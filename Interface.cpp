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
    this->PlaygroundTexture.free();
    this->gWallTexture.free();
    this->gOverTexture.free();
    this->gCreditTexture.free();
}

bool Interface::loadMedia(SDL_Renderer* &gRenderer)
{
    //Loading success flag
    bool success = true;

    this->PlaygroundTexture.loadFromFile(this->PlaygroundTexturePath, gRenderer);
    if (this->PlaygroundTexture.get_mTexture() == NULL) {
            success = false;
            printf( "Failed to load playgorund texture image %d!\n" );
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

//Rendering related textures

void Interface::renderPlayGround(SDL_Renderer* &gRenderer)
{
    this->PlaygroundTexture.render(gRenderer,0,0);

    SDL_RenderPresent( gRenderer);

    return;
}

void Interface::renderWall(SDL_Renderer* &gRenderer)
{
    this->gWallTexture.render(gRenderer,0,0);

    SDL_RenderPresent( gRenderer);

    return;
}

void Interface::renderGameOver(SDL_Renderer* &gRenderer)
{
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







