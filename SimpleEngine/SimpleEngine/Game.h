#pragma once
#include "Window.h"
#include "Renderer.h"

class Game
{
public:

	//SINGLETON, only one instance, accessed from everywhere
	static Game& instance() {
		static Game inst; //le static g�re la v�rification de "faut -il el cr�e, ou existe t-il deja)
		return inst;
	}

	Game(const Game&) = delete;
	Game& operator=(const Game&) = delete;
	Game(Game&&) = delete; //constructor par move
	Game& operator=(Game&&) = delete; //operateur d'attribution par move

private:
	Game() = default; //private constructor car c'est un singleton

public:
	bool initalize();
	void loop();
	void close();

private:
	void processInput();
	void update(float dt);
	void render();

	Window window {}; // <- appelle le constructor par d�faut
	bool isRunning {true};
	Renderer renderer {};
};

