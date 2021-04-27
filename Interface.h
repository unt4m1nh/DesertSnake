#ifndef INTERFACE_H
#define INTERFACE_H

#include<SDL.h>
#include<SDL_image.h>
#include<SDL_ttf.h>
#include<string>
#include "LTexture.h"
#include "Snake.h"


using namespace std;

class Interface
{
    public:
        Interface(SDL_Renderer* &gRenderer);
        ~Interface();

        void renderClassicGamePlay(SDL_Renderer* &gRenderer);
        void renderModernGamePlay(SDL_Renderer* &gRenderer);
        void renderGameOver(SDL_Renderer* &gRenderer);
        void renderCredit(SDL_Renderer* &gRenderer);
        void renderBackground(SDL_Renderer* &gRenderer);
        bool loadMedia(SDL_Renderer* &gRenderer);

        LTexture gBackgroundTexture;
        string gBackgroundTexturePath = "./images/background.png";

        LTexture gBoardTexture;
        string gBoardTexturePath = "./images/board.png";

        LTexture gWallTexture;
        string gWallTexturePath = "./images/wall.png";

        LTexture gOverTexture;
        string gOverTexturePath = "./images/over.png";

        LTexture gCreditTexture;
        string gCreditTexturePath = "./images/credit.jpg";


};


#endif // INTERFACE_H
