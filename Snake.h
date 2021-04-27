#ifndef SNAKE_H
#define SNAKE_H

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include<iostream>
#include<vector>
#include<string>

#include "LTexture.h"
#include "Config.h"
#include "Position.h"

using namespace std;

class Snake
{
public:
    Snake(SDL_Renderer* &gRenderer);
    ~Snake();

   int getStep();

   void handleEvent(SDL_Event& e, Mix_Chunk* gButton_Click);
   void classic();
   void modern();
   void growing();
   bool isHitWall();
   bool isBiteSelf();
   void currentPosition();


   void renderSnake(SDL_Renderer* &gRenderer);
   void reDraw(SDL_Renderer* &gRenderer);
   bool loadMedia(SDL_Renderer* &gRenderer);
   int direction = 1;
   vector<Point> snake = {
                         Point{SCREEN_WIDTH/2, SCREEN_HEIGHT/2},
                         Point{SCREEN_WIDTH/2, SCREEN_HEIGHT/2},
                         Point{SCREEN_WIDTH/2, SCREEN_HEIGHT/2},
                         Point{SCREEN_WIDTH/2, SCREEN_HEIGHT/2}
                      };
   Point prevTail;
   LTexture snakeTexture[100];
   string snakeTexturePath[2]={"./images/head.png",
                               "./images/body.png"};



private:
    int snakeWidth;
    int snakeHeight;
    const int step = 20;



};

#endif // SNAKE_H
