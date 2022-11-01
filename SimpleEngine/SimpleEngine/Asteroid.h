#pragma once
#include "Actor.h"

class Asteroid : public Actor
{
public:
	Asteroid();

	void updateActor(float dt) override;
};

