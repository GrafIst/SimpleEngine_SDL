#include "Game.h"
#include "Timer.h"

bool Game::initalize()
{
	bool isWindowInit = window.initalize();
	bool isRenderInit = renderer.initalize(window);
	return isWindowInit && isRenderInit;
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

void Game::close()
{
	renderer.close();
	window.close();
	SDL_Quit();
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
}

void Game::update(float dt)
{

}

void Game::render()
{
	renderer.beginDraw();

	renderer.endDraw();
}
