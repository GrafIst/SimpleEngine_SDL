#include "MoveComponent.h"
#include "Maths.h"
#include "Actor.h"
#include "Window.h"
#include "Log.h"
#include <iostream>

MoveComponent::MoveComponent(Actor* ownerP, int updateOrderP) : Component(ownerP, updateOrderP), 
forwardSpeed(0.0f), 
angularSpeed(0.0f),
mass(1.0f),
forces(Vector2::zero),
velocity(Vector2::zero),
acceleration(Vector2::zero),
maxVelocity(Vector2{100,100}),
horizontalDamp(0.0f)
{

}

void MoveComponent::setForwardSpeed(float forwardSpeedP)
{
	forwardSpeed = forwardSpeedP;
}

void MoveComponent::setAngularSpeed(float angularSpeedP)
{
	angularSpeed = angularSpeedP;
}

void MoveComponent::setMass(float massP) {
	mass = massP;
}

void MoveComponent::setMaxVelocity(Vector2 maxVelocityP)
{
	maxVelocity = maxVelocityP;
}

void MoveComponent::addForce(Vector2 forceP)
{
	forces += forceP; //add force to the sum of forces

}

void MoveComponent::removeForce(Vector2 forceP)
{
	forces -= forceP;
}

void MoveComponent::resetForce()
{
	forces = Vector2::zero;
}

void MoveComponent::resetVelocity()
{
	velocity = Vector2::zero;
}

void MoveComponent::update(float dt)
{

	//CALCULATE ACCELERATION   F = m * a <=> a = F / m
	acceleration.x = forces.x / mass;
	acceleration.y = forces.y / mass;

	//std::cout << "Acceleration Y : " << acceleration.y << std::endl;

	resetForce(); //reset forces after calculating the current acceleration

	//CALCULATE VELOCITY V = V + A * dT, make sure it's not over the max velocity
	Vector2 tempVelocity = velocity;
	tempVelocity = tempVelocity + (acceleration * dt);

	if (tempVelocity.x > maxVelocity.x) {
		tempVelocity.x = maxVelocity.x;
	}
	else if (tempVelocity.x < -maxVelocity.x) {
		tempVelocity.x = -maxVelocity.x;
	}

	if (tempVelocity.y > maxVelocity.y) {
		tempVelocity.y = maxVelocity.y;
	}
	else if (tempVelocity.y < -maxVelocity.y) {
		tempVelocity.y = -maxVelocity.y;
	}

	velocity.x = tempVelocity.x;
	velocity.y = tempVelocity.y;

	//CALCULATE NEW POSITION P = P + V * dt
	Vector2 newPosition = owner.getPosition() + (velocity * dt);
	if (newPosition.x < 0) { newPosition.x = WINDOW_WIDTH; }
	else if (newPosition.x > WINDOW_WIDTH) { newPosition.x = 0; }
	if (newPosition.y < 0) { newPosition.y = WINDOW_HEIGHT; }
	else if (newPosition.y > WINDOW_HEIGHT) { newPosition.y = 0; }

	owner.setPosition(newPosition);

	HorizontalDamping(dt);

	//NEED TO SETUP ANGULAR VELOCITY TOO
	if (!Maths::nearZero(angularSpeed)) {
		float newRotation = owner.getRotation() + angularSpeed * dt;
		owner.setRotation(newRotation);
	}

	


	//
	////keep forwardSpeed going unless the forwardSpeed is too slow
	//if (!Maths::nearZero(forwardSpeed)) {
	//	Vector2 newPosition = owner.getPosition() + owner.getForward() * forwardSpeed * dt;

	//	//Screen wrapping (for asteroids)
	//	if (newPosition.x < 0) { newPosition.x = WINDOW_WIDTH; }
	//	else if (newPosition.x > WINDOW_WIDTH) { newPosition.x = 0; }
	//	if (newPosition.y < 0) { newPosition.y = WINDOW_HEIGHT; }
	//	else if (newPosition.y > WINDOW_HEIGHT) { newPosition.y = 0; }

	//	owner.setPosition(newPosition);
	//}
}

void MoveComponent::HorizontalDamping(float dt)
{
	if (velocity.x > 0) { velocity.x -= (dt * horizontalDamp); }
	else if (velocity.x < 0) { velocity.x += (dt * horizontalDamp); }
	/*Log::info("Velocity Damping called");
	std::cout << "Velocity X : " << velocity.x << "| Velocity Y : " << velocity.y << std::endl;*/
}


