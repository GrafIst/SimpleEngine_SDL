#include "Asteroid.h"
#include "Random.h"
#include "Window.h"
#include "Maths.h"
#include "SpriteComponent.h"
#include "Assets.h"
#include "Game.h"

Asteroid::Asteroid() : Actor(), collision(nullptr), mc(nullptr)
{
	Vector2 randPos = Random::getVector(Vector2(0, 230), Vector2(WINDOW_WIDTH - 200, WINDOW_HEIGHT - 200));
	setPosition(randPos);
	setRotation(Random::getFloatRange(0.0f, Maths::twoPi));

	SpriteComponent* sc = new SpriteComponent(this, Assets::getTexture("Astroid"));
	mc = new MoveComponent(this);
	mc->setForwardSpeed(150.0f);
	mc->setMaxVelocity(Vector2{ 100.0f, 0.0f });

	collision = new CircleCollisionComponent(this);
	collision->setRadius(40.0f);

	getGame().addAsteroid(this);
}

Asteroid::~Asteroid()
{
	getGame().removeAsteroid(this);
}

void Asteroid::updateActor(float dt)
{
	//
	mc->addForce(Vector2::unitX * mc->getForwardSpeed());
}


