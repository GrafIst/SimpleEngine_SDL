#pragma once
#include "Actor.h"
#include <SDL_stdinc.h>
#include "CircleCollisionComponent.h"
#include "InputComponent.h"


class Ship : public Actor
{
public:
	Ship();

	void actorInput(const Uint8* keyState) override;
	void updateActor(float dt) override;

private:
	CircleCollisionComponent* collision;
	InputComponent* ic;
	float laserCooldown;
};

