#include <iostream>
#include <SDL.h>
#include "Log.h"
#include "Game.h"

int main(int argc, char** argv)
{
    auto& instance = Game::instance(); //auto, compilateur détermine tout seul le type de la variable
    bool isGameInit = instance.initalize();

    if (isGameInit) {
        instance.load();
        instance.loop();
        instance.unload();
    }
    instance.close();
    return 0;
}


