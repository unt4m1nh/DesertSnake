#include<iostream>
#include<string>
#include <ctime>
#include <cmath>

#include "Food.h"

using namespace std;

Food::Food(SDL_Renderer* &gRenderer)
{
    srand(time(0));
    this->loadMedia(gRenderer);
    this->setWidth(this->foodTexture.getWidth());
    this->setHeight(this->foodTexture.getHeight());
    this->set_x(100);
    this->set_y(100);
}

Food::~Food()
{
    this->foodTexture.free();
    this->setWidth(0);
    this->setHeight(0);
}

void Food::setWidth(int w)
{
    this->foodWidth = w;
}

void Food::setHeight(int h)
{
    this->foodHeight = h;
}

void Food::set_x(int x)
{
    this->x = x;
}

void Food::set_y(int y)
{
    this->y = y;
}


int Food::getWidth()
{
    return this->foodWidth;
}

int Food::getHeight()
{
    return this->foodHeight;
}


int Food::get_x()
{
    return this->x;
}

int Food::get_y()
{
    return this->y;
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

    /*
    TODO: draw the pacman character annimated
    */

    //Clear screen
    //SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
    //SDL_RenderClear( gRenderer );

    //Render texture to screen
    this->foodTexture.render(gRenderer,this->get_x(),this->get_y());


    SDL_RenderPresent( gRenderer );

    return;
}

//random ra toa do cua thuc an moi lan ran an thuc an
/*void Food::addFood()
{
    do
    {
        this->set_x(rand)
    }
}
*/
