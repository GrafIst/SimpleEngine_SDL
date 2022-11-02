#pragma once
#include "Component.h"
#include "Vector2.h"

class MoveComponent : public Component
{
public:
	MoveComponent(Actor* ownerP, int updateOrderP = 10); //update before other components
	MoveComponent() = delete;
	MoveComponent(const MoveComponent&) = delete;
	MoveComponent& operator=(const MoveComponent&) = delete;

	float getForwardSpeed() const { return forwardSpeed; }
	float getAngularSpeed() const { return angularSpeed; }
	float getMass() const { return mass; }

	void setForwardSpeed(float forwardSpeedP);
	void setAngularSpeed(float angularSpeedP);
	void setMass(float massP);
	void setMaxVelocity(Vector2 maxVelocityP);
	void setHorizontalDamp(float horizontalDampP) { horizontalDamp = horizontalDampP; }

	void addForce(Vector2 forceP);
	void removeForce(Vector2 forceP);

	void resetForce();
	void resetVelocity();

	void update(float dt) override;

	void HorizontalDamping(float dt);

private:
	float forwardSpeed;
	float angularSpeed;

	float mass;
	Vector2 forces;
	Vector2 velocity;
	Vector2 acceleration;
	Vector2 maxVelocity;
	float horizontalDamp;
};

