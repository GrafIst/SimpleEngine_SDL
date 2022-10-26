#include "Window.h"
#include "Log.h"

//Window::Window() : SDLWindow(nullptr), width(WINDOW_WIDTH), height(WINDOW_HEIGT)
//{
//
//}

bool Window::initalize()
{
	int sdlInitResult = SDL_Init(SDL_INIT_VIDEO);
	if (sdlInitResult != 0) {
		Log::error(LogCategory::Video, "Unable to initialize SDL");
		return false;
	}
	SDLWindow = SDL_CreateWindow("Spaceship", 100, 100, width, height, 0);
	if (!SDLWindow) {
	Log::error(LogCategory::System, "Failed to create window");
		return false;
	}
	return true;
}

void Window::close()
{
	SDL_DestroyWindow(SDLWindow);
}
