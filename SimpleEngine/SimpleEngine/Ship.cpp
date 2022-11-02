#include "Ship.h"
#include "SpriteComponent.h"
#include "Assets.h"
#include "InputComponent.h"
#include "Maths.h"
#include "AnimSpriteComponent.h"
#include "Laser.h"
#include "Game.h"
#include "Window.h"
#include "RectangleCollisionComponent.h"
#include "Log.h"

Ship::Ship() : Actor(), laserCooldown(0.0f), collision(nullptr), ic(nullptr) {
	//SpriteComponent* sc = new SpriteComponent(this, Assets::getTexture("Ship"));
	//i want to use the animated textures instead of the static SpriteComponent
	vector<Texture*> animTextures{
		&Assets::getTexture("Ship01"),
		&Assets::getTexture("Ship02"),
		&Assets::getTexture("Ship03"),
		&Assets::getTexture("Ship04"),
	};
	AnimSpriteComponent* asc = new AnimSpriteComponent(this, animTextures);
	ic = new InputComponent(this);
	ic->setMaxForwardSpeed(200.0f);
	ic->setMaxAngularSpeed(Maths::twoPi);
	ic->setMaxVelocity(Vector2{200.0f,180.0f});
	ic->setHorizontalDamp(15.0f);

	collision = new CircleCollisionComponent(this);
	collision->setRadius(20.0f);
}

void Ship::actorInput(const Uint8* keyState)
{
	//No need to shoot laser in my game

	/*if (keyState[SDL_SCANCODE_SPACE] && laserCooldown <= 0.0f) {
		Laser* laser = new Laser();
		laser->setPosition(getPosition());
		laser->setRotation(getRotation());
		laserCooldown = 0.2f;
	}*/
}

void Ship::updateActor(float dt)
{
	//Manage ship's gravity
	Vector2 gravity{ .0f, 9.81f };
	ic->addForce(gravity * 10);

	laserCooldown -= dt;

	//Manage ship collision
	
	//with ground
	auto ground = getGame().getGround();
	if (IntersectWithRectangle(*collision, ground->getCollision())) {
		//ca collide !
	}
	//TODO : collision check enntre CircleCollision and RectangleCollision

	//with asteroids
	auto asteroids = getGame().getAsteroids();
	for (auto asteroid : asteroids) {
		if (Interesct(*collision, asteroid->getCollision())) {
			auto centerPos = Vector2{ WINDOW_WIDTH / 2, 50 };
			setPosition(centerPos);
			setRotation(Maths::pi/2);
			ic->resetVelocity();
			break;
		}
	}
}


