#ifndef GAME_H
#define GAME_H

#include <SDL.h>
#include <SDL_image.h>
#include <iostream>

#include "Interface.h"
#include "Food.h"
#include "Snake.h"


class Game{

    /*public:
        const int width;
        const int height;
    */

    //private:
        //Position foodPosition;


    public:
        bool init();
        void close();
        bool run();

        // init function
        bool initWindowAndRender();
        bool initInterface(SDL_Renderer* &gRenderer);
        bool initFood(SDL_Renderer* &gRenderer);
        bool initSnake(SDL_Renderer* &gRenderer);


    private:
        // window game and renderer to draw
        // the game's characters, map, etc.
        SDL_Window* gWindow;
        SDL_Renderer* gRenderer;
        Interface* interface;
        Food* food;
        Snake* snake;

        //void addFood();

};


#endif // GAME_H
