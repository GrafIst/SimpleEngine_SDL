#include "Turret.h"
#include "SpriteComponent.h"
#include "Assets.h"
#include "Maths.h"
#include "Laser.h"
#include "Vector2.h"

Turret::Turret() : Actor(),shootDir(Vector2::zero), shootingCooldown(3.0f), aligningTargetCooldown(1.5f), targetShip(nullptr) {
	SpriteComponent* sc = new SpriteComponent(this, Assets::getTexture("Turret"));
}

void Turret::updateActor(float dt) {
	//MAKE Auto target system
	if (targetShip != nullptr) { //make sure the turret has a target

		if (aligningTargetCooldown <= 0) {
			shootDir = targetShip->getPosition() - getPosition();
			aligningTargetCooldown = 2.0f;
		}

		if (shootingCooldown <= 0) {
			Laser* laser = new Laser();
			laser->setPosition(getPosition());
			float rotateAngle = Vector2::radAngleBetween(Vector2::unitX, shootDir);
			laser->setRotation(rotateAngle);
			shootingCooldown = 3.0f;
		}

		shootingCooldown -= dt;
		aligningTargetCooldown -= dt;
	}
}

void Turret::setTarget(Ship* shipP)
{
	targetShip = shipP;
}
