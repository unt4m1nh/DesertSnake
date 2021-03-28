#include "Interface.h"

#include<SDL.h>
#include<SDL_image.h>
#include<string>

LTexture gRenderBackgroundTexture;

Interface::Interface(SDL_Renderer* &gRenderer)
{
    this->loadMedia(gRenderer);
}

Interface::~Interface()
{
    this->gBackgroundTexture.free();
    this->gBoardTexture.free();
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
    return success;
}

void Interface::renderCurrent(SDL_Renderer* &gRenderer)
{
               // SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
				//SDL_RenderClear( gRenderer );

				//Render background texture to screen
				this->gBackgroundTexture.render(gRenderer,0,0 );
				this->gBoardTexture.render(gRenderer,0,0);
				this->gWallTexture.render(gRenderer,0,0);

				//Update screen
				SDL_RenderPresent( gRenderer );

				return;
}
