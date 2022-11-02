#include "Ground.h"
#include "SpriteComponent.h"
#include "Assets.h"
#include "Window.h"
#include "Game.h"

Ground::Ground() : Actor(), collision(nullptr)
{
	SpriteComponent* sc = new SpriteComponent(this, Assets::getTexture("Ground"), 100);
	setPosition(Vector2{ WINDOW_WIDTH / 2, WINDOW_HEIGHT-10});

	collision = new RectangleCollisionComponent(this);
	collision->setHitbox(-(sc->getTextWidth() / 2), -(sc->getTexHeight() / 2), sc->getTextWidth() / 2, sc->getTexHeight() / 2);
	getGame().setGround(this);
}