#ifndef MENU_H
#define MENU_H

#include<iostream>
#include<SDL.h>
#include<SDL_image.h>
#include<string>

#include "LTexture.h"

using namespace std;

class Menu{



    public:

         Menu(SDL_Renderer* &gRenderer);
        ~Menu();

        void renderCurrent(SDL_Renderer* &gRenderer);
        bool loadMedia(SDL_Renderer* &gRenderer);

        LTexture gMenuTexture;
        string gMenuTexturePath = "./images/menu.png";





};


#endif // MENU_H
