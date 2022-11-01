#pragma once
#include "Actor.h"
#include "CircleCollisionComponent.h"

class Asteroid : public Actor
{
public:
	Asteroid();
	~Asteroid();

	CircleCollisionComponent& getCollision() { return *collision; }

	void updateActor(float dt) override;

private:
	CircleCollisionComponent* collision;
};

