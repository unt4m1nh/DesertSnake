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
    this->gWallTexture.free();
    this->gOverTexture.free();
    this->gCreditTexture.free();
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
    return success;
}

void Interface::renderClassicGamePlay(SDL_Renderer* &gRenderer)
{
    this->gBackgroundTexture.render(gRenderer,0,0);
    this->gBoardTexture.render(gRenderer,0,0);
    this->gWallTexture.render(gRenderer,0,0);

    SDL_RenderPresent( gRenderer );

    return;
}

void Interface::renderModernGamePlay(SDL_Renderer* &gRenderer)
{
    this->gBackgroundTexture.render(gRenderer,0,0);
    this->gBoardTexture.render(gRenderer,0,0);

    SDL_RenderPresent( gRenderer );

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

void Interface::renderBackground(SDL_Renderer* &gRenderer)
{
    this->gBackgroundTexture.render(gRenderer,0,0);

    SDL_RenderPresent( gRenderer);

    return;
}





