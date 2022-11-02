#pragma once
#include "Actor.h"
#include "RectangleCollisionComponent.h"

class Ground : public Actor
{
public:
	Ground();

	RectangleCollisionComponent& getCollision() { return *collision; }

private:
	RectangleCollisionComponent* collision;
};

