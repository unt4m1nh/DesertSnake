#ifndef SNAKE_H
#define SNAKE_H

#include <SDL.h>
#include <SDL_image.h>
#include<iostream>
#include<vector>
#include<string>

#include "LTexture.h"
#include "Config.h"

using namespace std;

struct Point
{
    int x0;
    int y0;
    int x = 0;
    int y = 0;
};

class Snake
{
public:
    Snake(SDL_Renderer* &gRenderer);
    ~Snake();

   void setWidth(int w);
   void setHeight(int h);
   void set_x(int x);
   void set_y(int y);
   int getWidth();
   int getHeight();
   int getVelocity();
   int get_x();
   int get_y();

   void handleEvent(SDL_Event& e);
   void move();


   void renderCurrent(SDL_Renderer* &gRenderer);
   bool loadMedia(SDL_Renderer* &gRenderer);

   int direction = 0;

   LTexture snakeTexture[1];
   string snakeTexturePath[1] = {"./images/head.png"};


private:
    int snakeWidth;
    int snakeHeight;
    const int VELOCITY = 20;

    Point snake[100];

};

#endif // SNAKE_H
