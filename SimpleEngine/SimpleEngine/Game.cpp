#include "Game.h"
#include "Timer.h"

bool Game::initalize()
{
	bool isWindowInit = window.initalize();
	bool isRenderInit = renderer.initalize(window);
	return isWindowInit && isRenderInit;
}

void Game::load()
{
	Assets::loadTexture(renderer, "Res/Ship01.png", "ship01");
	// si on utilise "\" il faut en mettre deux, ou utiliser le / normal

	//Doesn't open my texture for some reason
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
}

void Game::update(float dt)
{
	//Update actors
	isUpdatingActors = true;
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

	renderer.endDraw();
}
