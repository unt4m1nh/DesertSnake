#include "Snake.h"
#include "Food.h"
#include "Game.h"
#include "LTexture.h"


#include<iostream>
#include<vector>
#include<string>


using namespace std;

Snake::Snake(SDL_Renderer* &gRenderer)
{
    this->loadMedia(gRenderer);
}

Snake::~Snake()
{
  for(size_t i = 0; i < snake.size(); i++)
  {
      this->snakeTexture[i].free();
  }
}

int Snake::getStep()
{
    return this->step;
}



bool Snake::loadMedia(SDL_Renderer* &gRenderer)
{
    bool success = true;
    for (size_t i = 0; i < snake.size(); i++)
    {
        if(i==0)
        {
             this->snakeTexture[0].loadFromFile(this->snakeTexturePath[i],gRenderer);
        }
        else if (i == 1)
        {
             this->snakeTexture[1].loadFromFile(this->snakeTexturePath[i],gRenderer);
        }
        else
        {
             this->snakeTexture[i].loadFromFile(this->snakeTexturePath[(i+1)%i],gRenderer);
        }
    }
    for (size_t i = 0; i < snake.size(); i++) {
        if (this->snakeTexture[i].get_mTexture() == NULL) {
            success = false;
            printf( "Failed to load texture image %d!\n", i );
            break;
        }
    }

    return success;
}

void Snake::renderSnake(SDL_Renderer* &gRenderer)
{
    //render original snake
    for (size_t i = 0; i < snake.size(); i++)
    {
        this->snakeTexture[i].render(gRenderer,snake[i].x,snake[i].y,NULL,angle);
    }
    //redraw it when eating food
    for (size_t i = 1; i <= snake.size(); i++)
    {
        if(i == snake.size())
        {
             this->snakeTexture[0].render(gRenderer,snake[snake.size()-i].x,snake[snake.size()-i].y,NULL,angle);
        }
        else
        {
             this->snakeTexture[1].render(gRenderer,snake[snake.size()-i].x,snake[snake.size()-i].y,NULL,angle);
        }
    }
}

//handle event of snake
void Snake::handleEvent(SDL_Event& e, Mix_Chunk* gButton_Click)
{
    if( e.type == SDL_KEYDOWN && e.key.repeat == 0 )
     {
        if(e.key.keysym.sym == SDLK_UP && direction != 3)
        {
            angle = -90;
            Mix_PlayChannel(-1,gButton_Click,0);
            direction = 2;
        }
        else if(e.key.keysym.sym == SDLK_DOWN && direction != 2)
        {
            angle = 90;
            Mix_PlayChannel(-1,gButton_Click,0);
            direction = 3;
        }
        else if(e.key.keysym.sym == SDLK_LEFT && direction != 1)
        {
            angle = 180;
            Mix_PlayChannel(-1,gButton_Click,0);
            direction = 0;
        }
        else if(e.key.keysym.sym == SDLK_RIGHT && direction != 0)
        {
            angle = 0;
            Mix_PlayChannel(-1,gButton_Click,0);
            direction = 1;
        }
    }
}

//game logic of classic mode
void Snake::classic()
{
    prevTail = snake.back();
    for (size_t i = snake.size()-1; i > 0; i--)
		snake[i] = snake[i - 1];
    if (direction == 2)
            snake[0].y -= step;
    else if (direction == 3)
            snake[0].y += step;
    else if (direction == 0)
            snake[0].x -= step;
    else if (direction == 1)
            snake[0].x += step;

    if((snake[0].x < WALL) || (snake[0].x > SCREEN_WIDTH-200))
    {
        snake[0].x = snake[0].x;
    }

    if((snake[0].y < WALL) || (snake[0].y > SCREEN_HEIGHT - WALL*2))
    {
        snake[0].y = snake[0].y;
    }
}

//game logic of modern mode
void Snake::modern()
{
    prevTail = snake.back();
    for (size_t i = snake.size()-1; i > 0; i--)
		snake[i] = snake[i - 1];
    if (direction == 2)
            snake[0].y -= step;
    else if (direction == 3)
            snake[0].y += step;
    else if (direction == 0)
            snake[0].x -= step;
    else if (direction == 1)
            snake[0].x += step;

    if (snake[0].x < 0)
    {
        snake[0].x = SCREEN_WIDTH - 200;
    }
    if (snake[0].x > SCREEN_WIDTH - 200)
    {
        snake[0].x = 0;
    }
    if (snake[0].y < 0)
    {
        snake[0].y = SCREEN_HEIGHT - WALL;
    }
    if (snake[0].y > SCREEN_HEIGHT - WALL)
    {
        snake[0].y = 0;
    }
}

//adding Point to vector

void Snake::growing()
{
   this->snake.push_back(prevTail);
}


// check if snake hits wall
bool Snake::isHitWall()
{
    Point head = snake[0];
    return head.x == 0 || head.x == SCREEN_WIDTH - 200 || head.y == 0 || head.y == SCREEN_HEIGHT - 20;
}

//check if snake bites itself
bool Snake::isBiteSelf()
{
    Point head = snake[0];
    for (size_t i = 1; i < snake.size(); i++)
		if (head.x == snake[i].x && head.y == snake[i].y)
			return true;
    return false;
}
