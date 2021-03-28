#ifndef INTERFACE_H
#define INTERFACE_H

#include<SDL.h>
#include<SDL_image.h>
#include<string>
#include "LTexture.h"


using namespace std;

class Interface
{
    public:
        Interface(SDL_Renderer* &gRenderer);
        ~Interface();

        void renderCurrent(SDL_Renderer* &gRenderer);
        bool loadMedia(SDL_Renderer* &gRenderer);

        LTexture gBackgroundTexture;
        string gBackgroundTexturePath = "./images/flatds.jpg";

        LTexture gBoardTexture;
        string gBoardTexturePath = "./images/board.png";

        LTexture gWallTexture;
        string gWallTexturePath = "./images/wall.png";


};


#endif // INTERFACE_H
