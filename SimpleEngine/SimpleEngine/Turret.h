#pragma once
#include "Actor.h"
#include "Ship.h"

class Turret : public Actor
{
public:
	Turret();

	void updateActor(float dt) override;

	void setTarget(Ship* shipP);

private:
	Vector2 shootDir;
	float shootingCooldown;
	float aligningTargetCooldown;

	Ship* targetShip;
};

