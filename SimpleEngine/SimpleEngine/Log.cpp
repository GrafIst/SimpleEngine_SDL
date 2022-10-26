#include "Log.h"
#include <SDL_log.h>
#include <SDL_error.h>

void Log::info(const string& message) //passer en const reference qd on passe un object complexe, permet d'éviter les copies dans la mémoire, et l'object lui-même n'est pas modifiable "const")
{
	SDL_Log(message.c_str());
}

void Log::error(LogCategory category, const string& message)
{
	SDL_LogError(static_cast<int>(category),"%s | SDL: %s", message.c_str(), SDL_GetError());
	//static_cast plus précis que (int), donc plus important à utiliser
}
