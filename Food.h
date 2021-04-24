#ifndef FOOD_H
#define FOOD_H

#include<iostream>
#include<SDL.h>
#include<SDL_image.h>
#include<string>
#include "LTexture.h"
#include "Config.h"
#include "Position.h"

using namespace std;


class Food
{
    public:
        Food(SDL_Renderer* &gRenderer);
        ~Food();

         Point food = {Point{100,100}};



         void renderCurrent(SDL_Renderer* &gRenderer);
         bool loadMedia(SDL_Renderer* &gRenderer);

         LTexture foodTexture;
         string foodTexturePath = "./images/food.png";
    };

#endif // FOOD_H
