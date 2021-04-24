#include "Game.h"
#include "Config.h"
#include "Interface.h"
#include "Food.h"
#include "Snake.h"
#include "LTexture.h"
#include "TextObject.h"
#include "BaseObj.h"


#include<iostream>
#include<SDL.h>
#include<SDL_image.h>
#include<SDL_mixer.h>
#include<SDL_ttf.h>
#include<stdlib.h>
#include<ctime>
#include<string>


bool Game::initWindowAndRender() {

    // Initialization flag
    bool success = true;

	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
		success = false;
	}
	else
	{
		//Set texture filtering to linear
		if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
		{
			printf( "Warning: Linear texture filtering not enabled!" );
		}

		//Create window
		this->gWindow = SDL_CreateWindow( "DESERT SNAKE C++", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		if( this->gWindow == NULL )
		{
			printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
			success = false;
		}
		else
		{
			//Create renderer for window
			this->gRenderer = SDL_CreateRenderer( this->gWindow, -1, SDL_RENDERER_ACCELERATED );
			if( this->gRenderer == NULL )
			{
				printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
				success = false;
			}
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor( this->gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );

				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if( !( IMG_Init( imgFlags ) & imgFlags ) )
				{
					printf( "SDL_image could not initialize! SDL_mage Error: %s\n", IMG_GetError() );
					success = false;
				}
				if( Mix_OpenAudio( 22050, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
				{
					printf( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );
					success = false;
				}
				if( TTF_Init() == -1 )
				{
					printf( "SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError() );
					success = false;
				}
                gFont = TTF_OpenFont("./font/Lato-Bold.ttf",30);
                if(gFont == NULL)
                {
                    success = false;
                }
                gMusic = Mix_LoadMUS( "./audio/bgm.mp3" );
                if( gMusic == NULL )
                {
                    printf( "Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError() );
                    success = false;
                }
                gButton_Click = Mix_LoadWAV("./audio/button_click.mp3");
                if( gButton_Click == NULL )
                {
                    printf( "Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError() );
                    success = false;
                }
                gEat_Effect = Mix_LoadWAV("./audio/eat.mp3");
                if( gEat_Effect == NULL )
                {
                    printf( "Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError() );
                    success = false;
                }
                gHit_Effect = Mix_LoadWAV("./audio/hit.wav");
                if( gHit_Effect == NULL )
                {
                    printf( "Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError() );
                    success = false;
                }
			}
		}
	}

	return success;
}


bool Game::initInterface(SDL_Renderer* &gRenderer)
{
    this->interface = new Interface(gRenderer);

    return true;
}

bool Game::initFood(SDL_Renderer* &gRenderer)
{
    this->food = new Food(gRenderer);

    return true;
}

bool Game::initSnake(SDL_Renderer* &gRenderer)
{
    this->snake = new Snake(gRenderer);

    return true;
}

bool Game::initMenu(SDL_Renderer* &gRenderer)
{
    this->menu = new Menu(gRenderer);

    return true;
}

bool Game::initGame() {

    this->initWindowAndRender();
    this->initMenu(gRenderer);
    this->initInterface(gRenderer);
    this->initFood(gRenderer);
    this->initSnake(gRenderer);

    return true;
}

void Game::playMusic(Mix_Music* gMusic)
{
    Mix_PlayMusic( gMusic, -1 );

    return;
}

bool Game::eatFood()
{
   return this->snake->snake[0].x == this->food->food.x && this->snake->snake[0].y == this->food->food.y;
}

bool Game::checkCoordinate()
{
   for (int i = 0; i < this->snake->snake.size(); i++)
   {
       if (this->snake->snake[i].x == this->food->food.x && this->snake->snake[i].y == this->food->food.y)
       {
           return true;
       }
   }
   return false;
}



void Game::addFood()
{
        srand(time(0));
        vector <int> pos_X;
        vector <int> pos_Y;
        for(int i = 20; i < SCREEN_WIDTH - 200; i+=20)
        {
            pos_X.push_back(i);
        }
        for(int i = 20; i < SCREEN_HEIGHT - 20; i+=20)
        {
            pos_Y.push_back(i);
        }
        int randX = rand() % pos_X.size();
        int randY = rand() % pos_Y.size();
        this->food->food.x = pos_X[randX];
	    this->food->food.y = pos_Y[randY];
}


void Game::close() {

    delete(this->interface);
    delete(this->food);
    delete(this->snake);
    delete(this->menu);
    delete(this->text);
	//Destroy window
	SDL_DestroyRenderer( this->gRenderer );
	SDL_DestroyWindow( this->gWindow );
	Mix_FreeMusic( gMusic );
	TTF_CloseFont( gFont );
	gWindow = NULL;
	gRenderer = NULL;
	gMusic = NULL;


	//Quit SDL subsystems
	Mix_Quit();
	IMG_Quit();
	SDL_Quit();

    return;
}

bool Game::run() {
    //Main loop flag
    //bool quit_gameLoop = false;

    bool quit = false;

    bool modern = false;

    bool classic = false;

    bool check = false;

    TextObject score;
    score.set_color(TextObject::White_Text);
    int score_val = 0;

    //Event handler
    SDL_Event e;
    play_again:
        this->playMusic(gMusic);
        this->menu->renderCurrent(this->gRenderer);
        SDL_RenderPresent(gRenderer);
    while(!quit)
    {
         //Play the music
         while( SDL_PollEvent( &e ) != 0 )
         {
             if( e.type == SDL_KEYDOWN && e.key.repeat == 0 )
                {
                    if(e.key.keysym.sym == SDLK_s)
                    {
                        Mix_PlayChannel(-1,gButton_Click,0);
                        classic = true;
                        //quit = true;
                        Mix_PauseMusic();
                    }
                    if(e.key.keysym.sym == SDLK_m)
                    {
                        Mix_PlayChannel(-1,gButton_Click,0);
                        //modern = true;
                        //quit = true;
                        Mix_PauseMusic();
                    }
                    if(e.key.keysym.sym == SDLK_c)
                    {
                        Mix_PlayChannel(-1,gButton_Click,0);
                        this->interface->renderCredit(this->gRenderer);
                        SDL_RenderPresent(gRenderer);
                    }
                    if(e.key.keysym.sym == SDLK_q)
                    {
                        quit = true;
                    }
                }
         }
        while (classic == true)
        {
                srand(time(0));
                        //Handle events on queue and check when user deciced to quit game
                while( SDL_PollEvent( &e ) != 0 )
                {
                            //User requests quit
                    if( e.type == SDL_QUIT )
                    {
                        quit = true;
                    }

                    this->snake->handleEvent(e,gButton_Click);

                }

                this->snake->classic();

                if (this->eatFood())
                {
                    Mix_PlayChannel(-1,gEat_Effect,0);
                    this->snake->growing();
                    score_val += 20;
                    if (this->checkCoordinate() == true)
                    {
                        this->addFood();
                    }
                }
                if(this->snake->isHitWall() || this->snake->isBiteSelf() == true )
                {
                    Mix_PlayChannel(-1,gHit_Effect,0);
                    SDL_Delay(1000);
                    this->interface->renderGameOver(this->gRenderer);
                    SDL_Delay(5000);
                    classic = false;
                    quit = false;
                    score_val = 0;
                    goto play_again;
                }
                this->interface->renderCurrent(this->gRenderer);
                this->food->renderCurrent(this->gRenderer);
                this->snake->renderSnake(this->gRenderer);
                this->interface->renderWall(this->gRenderer);
                string str_score = to_string(score_val);
                score.SetText(str_score);
                score.LoadFromRenderText(gFont,gRenderer);
                if(score_val < 100)
                {
                  score.RenderText(gRenderer,700,100);
                }
                else if (score_val >= 100 && score_val < 1000)
                {
                  score.RenderText(gRenderer,690,100);
                }
                else
                {
                  score.RenderText(gRenderer,680,100);
                }

                SDL_RenderPresent(gRenderer);

                SDL_Delay(50);
        }

        if ( modern == true)
        {
                srand(time(0));
                while( SDL_PollEvent( &e ) != 0 )
                {
                    if( e.type == SDL_QUIT )
                    {
                        quit = true;
                    }

                    this->snake->handleEvent(e,gButton_Click);

                }
                this->snake->modern();

                if (this->eatFood())
                {
                    Mix_PlayChannel(-1,gEat_Effect,0);
                    score_val += 50;
                    this->snake->growing();
                    if (this->checkCoordinate() == true)
                    {
                        this->addFood();
                    }
                }
                if (this->snake->isBiteSelf() == true)
                {
                    Mix_PlayChannel(-1,gHit_Effect,0);
                    SDL_Delay(1000);
                    this->interface->renderGameOver(this->gRenderer);
                    SDL_Delay(5000);
                   // quit_gameLoop = true;

                }
                this->interface->renderCurrent(this->gRenderer);
                this->food->renderCurrent(this->gRenderer);
                this->snake->renderSnake(this->gRenderer);
                string str_score = to_string(score_val);
                score.SetText(str_score);
                score.LoadFromRenderText(gFont,gRenderer);
                if(score_val < 100)
                {
                  score.RenderText(gRenderer,700,100);
                }
                else if (score_val >= 100 && score_val < 1000)
                {
                  score.RenderText(gRenderer,690,100);
                }
                else
                {
                  score.RenderText(gRenderer,680,100);
                }
                SDL_RenderPresent(gRenderer);

                SDL_Delay(30);
        }
    }

     // End game and free the memory
    this->close();
    return true;
}




