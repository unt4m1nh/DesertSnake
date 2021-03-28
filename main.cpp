#include <iostream>
#include <SDL.h>
#include <SDL_image.h>

#include "Game.h"

using namespace std;


int main(int argc, char* args[]) {
    Game *game = new Game();

    // init the engine for running game
    game->init();

    // run the game
    game->run();

    return 0;
}
