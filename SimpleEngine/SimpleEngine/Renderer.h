#pragma once

#include <SDL.h>

//predeclare, only include in cpp, this is a good optimising method
class Window; 
struct Rectangle;

class Renderer
{
public:
	Renderer() = default;
	Renderer(const Renderer&) = delete;
	Renderer& operator=(const Renderer&) = delete;

	bool initalize(Window& window);
	void beginDraw();
	void drawRect(const Rectangle& rect);
	void endDraw();
	void close();

private:
	//SDL_Renderer* SDLRenderer = nullptr ; two way of initializing ?
	SDL_Renderer* SDLRenderer {nullptr};
};

