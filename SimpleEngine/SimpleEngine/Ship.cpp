#include "Ship.h"
#include "SpriteComponent.h"
#include "Assets.h"
#include "InputComponent.h"
#include "Maths.h"
#include "AnimSpriteComponent.h"
#include "Laser.h"

Ship::Ship() : Actor(), laserCooldown(0.0f) {
	//SpriteComponent* sc = new SpriteComponent(this, Assets::getTexture("Ship"));
	//i want to use the animated textures instead of the static SpriteComponent
	vector<Texture*> animTextures{
		&Assets::getTexture("Ship01"),
		&Assets::getTexture("Ship02"),
		&Assets::getTexture("Ship03"),
		&Assets::getTexture("Ship04"),
	};
	AnimSpriteComponent* asc = new AnimSpriteComponent(this, animTextures);
	InputComponent* ic = new InputComponent(this);
	ic->setMaxForwardSpeed(300.0f);
	ic->setMaxAngularSpeed(Maths::twoPi);
}

void Ship::actorInput(const Uint8* keyState)
{
	if (keyState[SDL_SCANCODE_SPACE] && laserCooldown <= 0.0f) {
		Laser* laser = new Laser();
		laser->setPosition(getPosition());
		laser->setRotation(getRotation());
		laserCooldown = 0.2f;
	}
}

void Ship::updateActor(float dt)
{
	laserCooldown -= dt;
}


