#include "Laser.h"
#include "SpriteComponent.h"
#include "Assets.h"
#include "Game.h"


Laser::Laser() : Actor(), deathTimer(2.0f), collision(nullptr), mc(nullptr)
{
	//new SpriteComponent(this, Assets::getTexture("Laser"));
	SpriteComponent* sc = new SpriteComponent(this, Assets::getTexture("Laser"));
	mc = new MoveComponent(this);
	mc->setForwardSpeed(800.0f);
	mc->setMaxVelocity(Vector2{ 1000,1000 });
	mc->setScreenWrapping(false);
	collision = new CircleCollisionComponent(this);
	collision->setRadius(11.0f);
}

void Laser::updateActor(float dt)
{
	//Vector2 forward{ .0f, 9.81f };
	mc->addForce(getForward()*1000);

	deathTimer -= dt;
	if (deathTimer <= 0.0f) {
		setState(Actor::ActorState::Dead);
	}
	else {

		//COLLISION WITH ASTEROID
		/*auto asteroids = getGame().getAsteroids();
		for (auto asteroid : asteroids) {
			if (Interesct(*collision, asteroid->getCollision())) {
				setState(ActorState::Dead);
				asteroid->setState(ActorState::Dead);
				break;
			}
		}*/

		auto player = getGame().getPlayer();
		if (Interesct(*collision, player->getCollision())) {
			setState(ActorState::Dead);
			player->Respawn();
		}
	}
}
