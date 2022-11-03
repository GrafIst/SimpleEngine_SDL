#include "Game.h"
#include "Actor.h"
#include "SpriteComponent.h"
#include "AnimSpriteComponent.h"
#include "Timer.h"
#include "Assets.h"
#include "BackgroundSpriteComponent.h"
#include "Asteroid.h"
#include "Maths.h"
#include "Ground.h"
#include "Turret.h"


bool Game::initalize()
{
	bool isWindowInit = window.initalize();
	bool isRenderInit = renderer.initalize(window);
	return isWindowInit && isRenderInit;
}

void Game::load()
{
	// Load textures
	Assets::loadTexture(renderer, "Res\\Ship01.png", "Ship01");
	Assets::loadTexture(renderer, "Res\\Ship02.png", "Ship02");
	Assets::loadTexture(renderer, "Res\\Ship03.png", "Ship03");
	Assets::loadTexture(renderer, "Res\\Ship04.png", "Ship04");
	Assets::loadTexture(renderer, "Res\\Farback01.png", "Farback01");
	Assets::loadTexture(renderer, "Res\\Farback02.png", "Farback02");
	Assets::loadTexture(renderer, "Res\\Stars.png", "Stars");
	Assets::loadTexture(renderer, "Res\\Astroid.png", "Astroid");
	Assets::loadTexture(renderer, "Res\\Laser.png", "Laser");

	Assets::loadTexture(renderer, "Res\\Ground.png", "Ground");
	Assets::loadTexture(renderer, "Res\\Turret.png", "Turret");

	// si on utilise "\" il faut en mettre deux, ou utiliser le / normal

	//Single sprite
	/*auto actor = new Actor();
	auto sprite = new SpriteComponent(actor, Assets::getTexture("Ship01"));
	actor->setPosition(Vector2{ 100, 100 });*/

	// Animated sprite
	/*vector<Texture*> animTextures{
		&Assets::getTexture("Ship01"),
		&Assets::getTexture("Ship02"),
		&Assets::getTexture("Ship03"),
		&Assets::getTexture("Ship04"),
	};*/
	//Actor* ship = new Actor();

	ground = new Ground();


	ship = new Ship();
	ship->setPosition(Vector2{ 20, 50 });
	ship->setRotation(0);

	Turret* leftTurret = new Turret();
	leftTurret->setPosition(Vector2{ 70, WINDOW_HEIGHT -100 });
	leftTurret->setTarget(ship);

	Turret* rightTurret = new Turret();
	rightTurret->setPosition(Vector2{ WINDOW_WIDTH-70, WINDOW_HEIGHT - 100 });
	rightTurret->setTarget(ship);


	/*const int astroidNumber =9;
	for (int i = 0; i < astroidNumber; ++i) {
		new Asteroid();
	}*/

	// Backgroundz
	// Create the "far back" background
	vector<Texture*> bgTexsFar{
		&Assets::getTexture("Farback01"),
		&Assets::getTexture("Farback02")
	};
	Actor* bgFar = new Actor();
	BackgroundSpriteComponent* bgSpritesFar = new BackgroundSpriteComponent(bgFar, bgTexsFar);
	bgSpritesFar->setScrollSpeed(-100.0f);

	// Create the closer background
	Actor* bgClose = new Actor();
	std::vector<Texture*> bgTexsClose{
		&Assets::getTexture("Stars"),
		&Assets::getTexture("Stars")
	};
	BackgroundSpriteComponent* bgSpritesClose = new BackgroundSpriteComponent(bgClose, bgTexsClose, 50);
	bgSpritesClose->setScrollSpeed(-200.0f);

}

void Game::loop()
{
	Timer timer {};
	float dt = 0;
	while (isRunning) {
		dt = timer.computeDeltaTime() / 1000.0f;
		processInput();
		update(dt);
		render();
		timer.delayTime();
	}
}

void Game::unload()
{
	while (!actors.empty()) {
		delete actors.back();
	}

	Assets::clear();
}

void Game::close()
{
	renderer.close();
	window.close();
	SDL_Quit();
}

void Game::addActor(Actor* actor)
{
	if (isUpdatingActors) {
		pendingActors.emplace_back(actor);
	}
	else {
		actors.emplace_back(actor);
	}
}

void Game::removeActor(Actor* actor)
{
	//Erase actor from the two vectors
	auto iter = std::find(begin(pendingActors), end(pendingActors), actor);
	//QA : Quelle est la différence entre begin() et .begin() avec les iterators
	//REPONSE : différence de version, .begin (c++11) et begin() (c++14)

	if (iter != end(pendingActors)) {
		//Swap to end of vector and pop off (avoid erase copies)
		std::iter_swap(iter, end(pendingActors) - 1);
		pendingActors.pop_back();
	}
	iter = std::find(begin(actors), end(actors), actor);
	if (iter != end(actors))
	{
		std::iter_swap(iter, end(actors) - 1);
		actors.pop_back();
	}
}

void Game::processInput()
{
	//SDL EVENT
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		switch (event.type) {
		case SDL_QUIT:
			isRunning = false;
			break;
		}
	}

	const Uint8* keyboardState = SDL_GetKeyboardState(nullptr);
	//Escape : quit game
	if (keyboardState[SDL_SCANCODE_ESCAPE]) {
		isRunning = false;
	}

	//Actor input
	isUpdatingActors = true;
	for (auto actor : actors) {
		actor->processInput(keyboardState);
	}
	isUpdatingActors = false;
}

void Game::update(float dt)
{
	//Update actors
	isUpdatingActors = true; //if it's updating, safety so we don't add actors to the loop, (put in pendingactor)
	for (auto actor : actors) {
		actor->update(dt);
	}
	isUpdatingActors = false;

	//Move pending actors to actors
	for (auto pendingActor : pendingActors)
	{
		actors.emplace_back(pendingActor);
	}
	pendingActors.clear();

	//Delete dead actors
	vector<Actor*> deadActors;
	for (auto actor : actors) {
		if (actor->getState() == Actor::ActorState::Dead) {
			deadActors.emplace_back(actor);
		}
	}
	for (auto deadActor : deadActors) {
		delete deadActor;
	}
}

void Game::render()
{
	renderer.beginDraw();
	renderer.draw();
	renderer.endDraw();
}

vector<Asteroid*>& Game::getAsteroids()
{
	return asteroids;
}

void Game::addAsteroid(Asteroid* asteroid)
{
	asteroids.emplace_back(asteroid);
}

void Game::removeAsteroid(Asteroid* asteroid)
{
	auto iter = std::find(begin(asteroids), end(asteroids), asteroid);
	if (iter != asteroids.end()) {
		asteroids.erase(iter);
	}
}


