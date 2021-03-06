#ifndef GAME_H
#define GAME_H

#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <SDL_mixer.h>
#include <SDL_ttf.h>


#include "Interface.h"
#include "Food.h"
#include "Snake.h"
#include "Menu.h"
#include "TextObject.h"


class Game{

    public:
        bool initGame();
        void close();
        bool run();
        bool playAgain();
        bool eatFood();
        void addFood();
        bool checkCoordinate();
        void playMusic(Mix_Music* gMusic);
        void getHighScore();
        void resetClassic();
        void resetModern();
        int checkClassicHighScore();
        int checkModernHighScore();
        void setClassicHighScore(int highscore);
        void setModernHighScore(int highscore);


        // init function
        bool initWindowAndRender();
        bool initInterface(SDL_Renderer* &gRenderer);
        bool initFood(SDL_Renderer* &gRenderer);
        bool initSnake(SDL_Renderer* &gRenderer);
        bool initMenu(SDL_Renderer* &gRenderer);

        Mix_Music* gMusic = NULL;
        Mix_Chunk* gButton_Click = NULL;
        Mix_Chunk* gEat_Effect = NULL;
        Mix_Chunk* gHit_Effect = NULL;
        TTF_Font* TextTexture1 = NULL;
        TTF_Font* TextTexture2 = NULL;
        TTF_Font* TextTexture3 = NULL;


        int classic_score_val = 0;
        int modern_score_val = 0;
        int highscore;


    private:
        SDL_Window* gWindow;
        SDL_Renderer* gRenderer;
        Interface* interface;
        Food* food;
        Snake* snake;
        Menu* menu;
        TextObject* text;

};


#endif // GAME_H
