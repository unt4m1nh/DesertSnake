#include "Menu.h"
#include "Config.h"

#include<iostream>
#include<SDL.h>
#include<SDL_image.h>


Menu::Menu(SDL_Renderer* &gRenderer)
{
    this->loadMedia(gRenderer);
}

Menu::~Menu()
{
    this->gMenuTexture.free();
}
bool Menu::loadMedia(SDL_Renderer* &gRenderer)
{
    //Loading success flag
    bool success = true;

    //Load Background texture
    this->gMenuTexture.loadFromFile(this->gMenuTexturePath, gRenderer);
    if (this->gMenuTexture.get_mTexture() == NULL) {
            success = false;
            printf( "Failed to load background texture image %d!\n" );
    }
    return success;

}

void Menu::renderCurrent(SDL_Renderer* &gRenderer)
{
    this->gMenuTexture.render(gRenderer,0,0 );


    SDL_RenderPresent( gRenderer );

    return;
}



