#pragma once
#include <SDL.h>

constexpr int WINDOW_WIDTH = 1024; //constexp au lien de const, apparement cest mieux
constexpr int WINDOW_HEIGHT = 768;

class Window
{
public:
	//Window(); //pas nécessaire car les variables sont initialize par defaut (23-25)
	//enfaite non, necessaire car on a besoin du constructor par défaut dans Game.h
	Window() = default;
	
	Window(const Window&) = delete;
	Window& operator=(const Window&) = delete;

	bool initalize();
	void close();

	//classique Getters, dans le header, + opti pour le compilateur
	SDL_Window* getSDLWindow() const { return SDLWindow; }
	int getWidth() const { return width; }
	int getHeight() const { return height; }


private:
	SDL_Window* SDLWindow {nullptr}; //tjr initialisé un pointer par un nullptr
	int width{ WINDOW_WIDTH };
	int height{ WINDOW_HEIGHT };
};

