#include "Log.h"
#include <SDL_log.h>
#include <SDL_error.h>

void Log::info(const string& message) //passer en const reference qd on passe un object complexe, permet d'�viter les copies dans la m�moire, et l'object lui-m�me n'est pas modifiable "const")
{
	SDL_Log(message.c_str());
}

void Log::error(LogCategory category, const string& message)
{
	SDL_LogError(static_cast<int>(category),"%s | SDL: %s", message.c_str(), SDL_GetError());
	//static_cast plus pr�cis que (int), donc plus important � utiliser
}
