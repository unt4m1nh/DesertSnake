#include<iostream>
#include<string>

#include "Food.h"

using namespace std;

Food::Food(SDL_Renderer* &gRenderer)
{
    this->loadMedia(gRenderer);
}

Food::~Food()
{
    this->foodTexture.free();
}

bool Food::loadMedia(SDL_Renderer* &gRenderer) {
    //Loading success flag
    bool success = true;
    this->foodTexture.loadFromFile(this->foodTexturePath, gRenderer);
    if (this->foodTexture.get_mTexture() == NULL) {
            success = false;
            printf( "Failed to load texture image %d!\n" );
    }

    return success;
}

void Food::renderCurrent(SDL_Renderer *&gRenderer) {

    this->foodTexture.render(gRenderer,food.x,food.y);


    SDL_RenderPresent( gRenderer );

    return;
}




