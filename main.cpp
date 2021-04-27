#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>


#include "Game.h"


using namespace std;



int main(int argc, char* args[]) {


    Game *game = new Game();

    game->initGame();

    game->run();

    //game->getHighScore();

    return 0;
}


