#pragma once

#include <string>
using std::string;
#include <SDL_log.h>

enum class LogCategory { //this is called a wrapper
	Application = SDL_LOG_CATEGORY_APPLICATION,
	Assert = SDL_LOG_CATEGORY_ASSERT,
	Audio = SDL_LOG_CATEGORY_AUDIO,
	Error = SDL_LOG_CATEGORY_ERROR,
	Input = SDL_LOG_CATEGORY_INPUT,
	Render = SDL_LOG_CATEGORY_RENDER,
	System = SDL_LOG_CATEGORY_SYSTEM,
	Test = SDL_LOG_CATEGORY_TEST,
	Video = SDL_LOG_CATEGORY_VIDEO
};

class Log
{
public:
	Log() = delete; // soit delete, soit default (si on veut que cpp implemente tout seul car �vident)
	Log(const Log&) = delete;
	Log& operator=(const Log&) = delete; //delete aussi l'op�rateur '='

	static void info(const string& message);
	static void error(LogCategory category, const string& message);
};

