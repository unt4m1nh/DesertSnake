#include "Interface.h"
#include "Config.h"
#include "Game.h"

#include<SDL.h>
#include<SDL_image.h>
#include<string>



Interface::Interface(SDL_Renderer* &gRenderer)
{
    this->loadMedia(gRenderer);
}

Interface::~Interface()
{
    this->gBackgroundTexture.free();
    this->gBoardTexture.free();
    this->gOverTexture.free();
    this->gCreditTexture.free();
    this->gScoreBoardTexture.free();
    this->gPlayAgainTexture.free();
}

bool Interface::loadMedia(SDL_Renderer* &gRenderer)
{
    //Loading success flag
    bool success = true;

    //Load Background texture
    this->gBackgroundTexture.loadFromFile(this->gBackgroundTexturePath, gRenderer);
    if (this->gBackgroundTexture.get_mTexture() == NULL) {
            success = false;
            printf( "Failed to load background texture image %d!\n" );
    }

    this->gBoardTexture.loadFromFile(this->gBoardTexturePath, gRenderer);
    if (this->gBoardTexture.get_mTexture() == NULL) {
            success = false;
            printf( "Failed to load board texture image %d!\n" );
    }

    this->gWallTexture.loadFromFile(this->gWallTexturePath, gRenderer);
    if (this->gWallTexture.get_mTexture() == NULL) {
            success = false;
            printf( "Failed to load wall texture image %d!\n" );
    }
    this->gOverTexture.loadFromFile(this->gOverTexturePath, gRenderer);
    if (this->gOverTexture.get_mTexture() == NULL) {
            success = false;
            printf( "Failed to load over texture image %d!\n" );
    }
    this->gCreditTexture.loadFromFile(this->gCreditTexturePath, gRenderer);
    if (this->gCreditTexture.get_mTexture() == NULL) {
            success = false;
            printf( "Failed to load credit texture image %d!\n" );
    }
    this->gScoreBoardTexture.loadFromFile(this->gScoreBoardTexturePath, gRenderer);
    if (this->gScoreBoardTexture.get_mTexture() == NULL) {
            success = false;
            printf( "Failed to load scoreboard texture image %d!\n" );
    }
    this->gPlayAgainTexture.loadFromFile(this->gPlayAgainTexturePath, gRenderer);
    if (this->gPlayAgainTexture.get_mTexture() == NULL) {
            success = false;
            printf( "Failed to load play again texture image %d!\n" );
    }
}

void Interface::renderCurrent(SDL_Renderer* &gRenderer)
{
               // SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
				//SDL_RenderClear( gRenderer );

				//Render background texture to screen
				this->gBackgroundTexture.render(gRenderer,0,0 );
				this->gBoardTexture.render(gRenderer,0,0);
				this->gScoreBoardTexture.render(gRenderer,665,50);

				//Update screen
				SDL_RenderPresent( gRenderer );

				return;
}

void Interface::renderWall(SDL_Renderer* &gRenderer)
{
    this->gWallTexture.render(gRenderer,0,0);

    SDL_RenderPresent(gRenderer);

    return;
}

void Interface::renderGameOver(SDL_Renderer* &gRenderer)
{
    //SDL_RenderClear( gRenderer);
    this->gOverTexture.render(gRenderer,100, 40 );

    SDL_RenderPresent( gRenderer );

    return;
}

void Interface::renderCredit(SDL_Renderer* &gRenderer)
{
    this->gCreditTexture.render(gRenderer,0,0);

    SDL_RenderPresent( gRenderer);

    return;
}

void Interface::renderPlayAgain(SDL_Renderer* &gRenderer)
{
    this->gPlayAgainTexture.render(gRenderer,0,0);

    SDL_RenderPresent(gRenderer);

    return;
}


