#pragma once
#include "Window.h"
#include "Renderer.h"
#include <vector>
#include "Vector2.h"
#include "Actor.h"
#include "Assets.h"
#include "SpriteComponent.h"
#include "Asteroid.h"
#include "Ground.h"
#include "Ship.h"

using std::vector;

class Game
{
public:

	//SINGLETON, only one instance, accessed from everywhere
	static Game& instance() {
		static Game inst; //le static gère la vérification de "faut -il el crée, ou existe t-il deja)
		return inst;
	}

	Game(const Game&) = delete;
	Game& operator=(const Game&) = delete;
	Game(Game&&) = delete; //constructor par move
	Game& operator=(Game&&) = delete; //operateur d'attribution par move

private:
	Game() : isRunning(true), isUpdatingActors(false) {}; //private constructor car c'est un singleton

public:
	bool initalize();
	void load();
	void loop();
	void unload();
	void close();

	void addActor(Actor* actor);
	void removeActor(Actor* actor);

	Renderer& getRenderer() { return renderer; }

private:
	void processInput();
	void update(float dt);
	void render();

	bool isRunning;
	Window window {}; // <- appelle le constructor par défaut
	Renderer renderer {};

	bool isUpdatingActors;
	vector<Actor*> actors;
	vector<Actor*> pendingActors;
	/*We don't want to insert actors in the middle of the actors' 
	update loop*/

	//GAME SPECIFIC
public:
	vector<Asteroid*>& getAsteroids();
	void addAsteroid(Asteroid* asteroid);
	void removeAsteroid(Asteroid* asteroid);
	Ground* getGround() { return ground; };
	void setGround(Ground* groundP) { ground = groundP; }
	Ship* getPlayer() { return ship; };

	void playerWon();

private:
	vector<Asteroid*> asteroids;
	Ground* ground;
	Ship* ship;
};

