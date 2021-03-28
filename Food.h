#ifndef FOOD_H
#define FOOD_H

#include<iostream>
#include<SDL.h>
#include<SDL_image.h>
#include<string>
#include "LTexture.h"
#include "Config.h"

using namespace std;

class Food
{
    public:
        Food(SDL_Renderer* &gRenderer);
        ~Food();

         void setWidth(int w);
         void setHeight(int h);
         void set_x(int x);
         void set_y(int y);
         int getWidth();
         int getHeight();
         int get_x();
         int get_y();

         void handleEvent(SDL_Event& e);
         void addFood();

         void renderCurrent(SDL_Renderer* &gRenderer);
         bool loadMedia(SDL_Renderer* &gRenderer);

         LTexture foodTexture;
         string foodTexturePath = "./images/food.png";
    private:
         int foodWidth;
         int foodHeight;
         int x;
         int y;

    };

#endif // FOOD_H
