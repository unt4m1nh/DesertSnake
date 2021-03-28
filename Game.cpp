#include "Game.h"
#include "Config.h"
#include "Interface.h"
#include "Food.h"


#include<iostream>
#include<SDL.h>
#include<SDL_image.h>

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

bool Game::initFood(SDL_Renderer * &gRenderer) {
    this->food = new Food(gRenderer);

    return true;
}

bool Game::initSnake(SDL_Renderer* &gRenderer)
{
    this->snake = new Snake(gRenderer);

    return true;
}



bool Game::init() {
    /*
    Init function that inits all window, render, and characters such as pacman, ghosts, map, etc
    */

    /*
    TODO: add success flag to check if initize success or not
    */

    this->initWindowAndRender();
    this->initInterface(gRenderer);
    this->initFood(gRenderer);
    this->initSnake(gRenderer);

    return true;
}

void Game::close() {

    delete(this->interface);
    delete(this->food);
    delete(this->snake);
	//Destroy window
	SDL_DestroyRenderer( this->gRenderer );
	SDL_DestroyWindow( this->gWindow );
	gWindow = NULL;
	gRenderer = NULL;

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();

    return;
}

bool Game::run() {
    //Main loop flag
    bool quit = false;

    //Event handler
    SDL_Event e;

    // Game loop. This contain game action
    while( !quit )
    {
        //Handle events on queue and check when user deciced to quit game
        while( SDL_PollEvent( &e ) != 0 )
        {
            //User requests quit
            if( e.type == SDL_QUIT )
            {
                quit = true;
            }
            // Handle characters' events

            this->snake->handleEvent(e);

        }

        // Handle game logic in here
        /*
        TODO: add game logic in here
        */

        /*
        Note that we define render in each object as this function, and in engine, we check the state of each
        object and call this render function to draw on the screen
        */
        this->snake->move();
        // First, just render the character
        this->interface->renderCurrent(this->gRenderer);
        this->food->renderCurrent(this->gRenderer);
        this->snake->renderCurrent(this->gRenderer);

        SDL_RenderPresent(gRenderer);
        SDL_Delay(60);
    }

    // End game and free the memory
    this->close();

    return true;
}





