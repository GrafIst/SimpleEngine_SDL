#pragma once
#include "Actor.h"
#include <SDL_stdinc.h>
#include "CircleCollisionComponent.h"
#include "InputComponent.h"


class Ship : public Actor
{
public:

	enum class ShipState {
		Flying, Landed
	};

	Ship();

	void actorInput(const Uint8* keyState) override;
	void updateActor(float dt) override;

	void setPosition(Vector2 positionP) override;

	void Land();
	void setShipState(ShipState stateP);
	CircleCollisionComponent& getCollision() { return *collision; }

	void Respawn();


private:
	CircleCollisionComponent* collision;
	InputComponent* ic;
	float laserCooldown;
	ShipState shipState;
};

