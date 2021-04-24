#include "Snake.h"

#include<iostream>
#include<vector>
#include<string>

using namespace std;

Snake::Snake(SDL_Renderer* &gRenderer)
{
    this->loadMedia(gRenderer);
    this->setHeight(this->snakeTexture[0].getHeight());
    this->setWidth(this->snakeTexture[0].getWidth());
    this->set_x(SCREEN_WIDTH/2.5);
    this->set_y(SCREEN_HEIGHT/2);

}

Snake::~Snake()
{
  for(int i = 0; i < 4; i++)
  {
      this->snakeTexture[i].free();
  }
}

void Snake::setWidth(int w)
{
    this->snakeWidth = w;
}

void Snake::setHeight(int h)
{
    this->snakeHeight = h;
}

void Snake::set_x(int x)
{
    this->snake[0].x0 = x;
}

void Snake::set_y(int y)
{
    this->snake[0].y0 = y;
}


int Snake::getWidth()
{
    return this->snakeWidth;
}

int Snake::getHeight()
{
    return this->snakeHeight;
}

int Snake::getVelocity()
{
    return this->VELOCITY;
}

int Snake::get_x()
{
    return this->snake[0].x0;
}

int Snake::get_y()
{
    return this->snake[0].y0;
}


bool Snake::loadMedia(SDL_Renderer* &gRenderer)
{
    bool success = true;
    for (int i = 0; i < 4; i++)
    {
        if(i==0)
        {
            this->snakeTexture[0].loadFromFile(this->snakeTexturePath[0],gRenderer);
        }
        else
        {
            this->snakeTexture[i].loadFromFile(this->snakeTexturePath[(i+1)%i],gRenderer);
        }
    }
    for (int i = 0; i < 4; i++) {
        if (this->snakeTexture[i].get_mTexture() == NULL) {
            success = false;
            printf( "Failed to load texture image %d!\n", i );
            break;
        }
    }

    return success;
}

void Snake::renderSnakeHead(SDL_Renderer* &gRenderer)
{
    for (int i = 0; i < 4; i++)
    {
        this->snakeTexture[i].render(gRenderer,this->get_x(),this->get_y());
    }
    return;
}

void Snake::handleEvent(SDL_Event& e)
{
    if( e.type == SDL_KEYDOWN && e.key.repeat == 0 )
     {
        //Adjust the velocity
        switch( e.key.keysym.sym )
        {
            case SDLK_UP: snake[0].y -= VELOCITY; direction = 2; break;
            case SDLK_DOWN: snake[0].y += VELOCITY; direction = 3; break;
            case SDLK_LEFT: snake[0].x -= VELOCITY; direction = 0; break;
            case SDLK_RIGHT: snake[0].x += VELOCITY; direction = 1; break;
        }
    }
    else if( e.type == SDL_KEYUP && e.key.repeat == 0 )
    {
        //Adjust the velocity
        switch( e.key.keysym.sym )
        {
            case SDLK_UP: snake[0].y += VELOCITY; break;
            case SDLK_DOWN: snake[0].y -= VELOCITY; break;
            case SDLK_LEFT: snake[0].x += VELOCITY; break;
            case SDLK_RIGHT: snake[0].x -= VELOCITY; break;
        }
    }
}

void Snake::move()
{
    /*for (int i = 0;i < snake.size();i++){
		if (i == 0){
			this->snake[0].x0 = this->snake[0].x;this->snake[0].y0 = this->snake[0].y;
		}
		else {
			this->snake[i].x0 = this->snake[i].x;this->snake[i].y0 = this->snake[i].y;
			this->snake[i].x = this->snake[i-1].x0;this->snake[i].y = this->snake[i-1].y0;
		}
    */

    this->snake[0].x0 += this->snake[0].x;
    //this->snake[1].x0 = this->snake[0].x;
      //this->snake[i].x0 += this->snake[0].x;

    if((snake[0].x0 < WALL*2) || (snake[0].x0 + this->getWidth() > SCREEN_WIDTH-220))
    {
        snake[0].x0 = snake[0].x0;
    }

    this->snake[0].y0 += this->snake[0].y;
    //this->snake[1].y0 = this->snake[0].y;
      //this->snake[i].y0 += this->snake[0].y;
    if((snake[0].y0 < WALL*2) || (snake[0].y0 + this->getHeight() > SCREEN_HEIGHT - WALL*2))
    {
        snake[0].y0 = snake[0].y0;
    }
 		/*
		  TO DO: check game ending
        */

}

bool Snake::checkInsideBox()
{
    if((snake[0].x0 < WALL * 2) || (snake[0].x0 + this->getWidth() > SCREEN_WIDTH - 220))
    {
        return true;
    }
    if((snake[0].y0 < WALL * 2) || (snake[0].y0 + this->getHeight() > SCREEN_HEIGHT - WALL*2))
    {
        return true;
    }
    return false;
}
