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

        void renderCurrent(SDL_Renderer* &gRenderer);
        void renderGameOver(SDL_Renderer* &gRenderer);
        void renderCredit(SDL_Renderer* &gRenderer);
        void renderWall(SDL_Renderer* &gRenderer);
        void renderPlayAgain(SDL_Renderer* &gRenderer);
        bool loadMedia(SDL_Renderer* &gRenderer);

        LTexture gBackgroundTexture;
        string gBackgroundTexturePath = "./images/flatds.jpg";

        LTexture gBoardTexture;
        string gBoardTexturePath = "./images/board.png";

        LTexture gWallTexture;
        string gWallTexturePath = "./images/wall.png";

        LTexture gOverTexture;
        string gOverTexturePath = "./images/over.png";

        LTexture gCreditTexture;
        string gCreditTexturePath = "./images/credit.jpg";

        LTexture gScoreBoardTexture;
        string gScoreBoardTexturePath = "./images/scoreboard.png";

        LTexture gPlayAgainTexture;
        string gPlayAgainTexturePath = "./images/playagain.png";



};


#endif // INTERFACE_H
