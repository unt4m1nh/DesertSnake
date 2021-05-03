#include "Game.h"
#include "Config.h"
#include "Interface.h"
#include "Food.h"
#include "Snake.h"
#include "LTexture.h"
#include "TextObject.h"


#include<iostream>
#include<SDL.h>
#include<SDL_image.h>
#include<SDL_mixer.h>
#include<SDL_ttf.h>
#include<stdlib.h>
#include<ctime>
#include<string>
#include<fstream>


bool Game::initWindowAndRender() {

    // Initialization flag
    bool success = true;

	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
		success = false;
	}
	else
	{
		//Set texture filtering to linear
		if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
		{
			printf( "Warning: Linear texture filtering not enabled!" );
		}

		//Create window
		this->gWindow = SDL_CreateWindow( "SNAKE C++", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		if( this->gWindow == NULL )
		{
			printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
			success = false;
		}
		else
		{
			//Create renderer for window
			this->gRenderer = SDL_CreateRenderer( this->gWindow, -1, SDL_RENDERER_ACCELERATED );
			if( this->gRenderer == NULL )
			{
				printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
				success = false;
			}
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor( this->gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );

				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if( !( IMG_Init( imgFlags ) & imgFlags ) )
				{
					printf( "SDL_image could not initialize! SDL_mage Error: %s\n", IMG_GetError() );
					success = false;
				}
                // Load text texture by TTF_Init
				if( TTF_Init() == -1 )
				{
					printf( "SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError() );
					success = false;
				}
                TextTexture1 = TTF_OpenFont("./font/Lato-Bold.ttf",30);
                if( TextTexture1 == NULL)
                {
                    success = false;
                }
                TextTexture2 = TTF_OpenFont("./font/FFF_Tusj.ttf",60);
                if( TextTexture2 == NULL )
                {
                    success = false;
                }
                TextTexture3 = TTF_OpenFont("./font/FFF_Tusj.ttf",80);
                if( TextTexture3 == NULL )
                {
                    success = false;
                }
                // Load audio texture
                if( Mix_OpenAudio( 22050, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
				{
					printf( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );
					success = false;
				}
                gMusic = Mix_LoadMUS( "./audio/bgm.mp3" );
                if( gMusic == NULL )
                {
                    printf( "Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError() );
                    success = false;
                }
                gButton_Click = Mix_LoadWAV("./audio/button_click.mp3");
                if( gButton_Click == NULL )
                {
                    printf( "Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError() );
                    success = false;
                }
                gEat_Effect = Mix_LoadWAV("./audio/eat.mp3");
                if( gEat_Effect == NULL )
                {
                    printf( "Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError() );
                    success = false;
                }
                gHit_Effect = Mix_LoadWAV("./audio/hit.wav");
                if( gHit_Effect == NULL )
                {
                    printf( "Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError() );
                    success = false;
                }
			}
		}
	}

	return success;
}


bool Game::initInterface(SDL_Renderer* &gRenderer)
{
    this->interface = new Interface(gRenderer);

    return true;
}

bool Game::initFood(SDL_Renderer* &gRenderer)
{
    this->food = new Food(gRenderer);

    return true;
}

bool Game::initSnake(SDL_Renderer* &gRenderer)
{
    this->snake = new Snake(gRenderer);

    return true;
}

bool Game::initMenu(SDL_Renderer* &gRenderer)
{
    this->menu = new Menu(gRenderer);

    return true;
}

bool Game::initGame() {

    this->initWindowAndRender();
    this->initMenu(gRenderer);
    this->initInterface(gRenderer);
    this->initFood(gRenderer);
    this->initSnake(gRenderer);

    return true;
}

void Game::playMusic(Mix_Music* gMusic)
{
    Mix_PlayMusic( gMusic, -1 );

    return;
}

bool Game::eatFood()
{
   return this->snake->snake[0].x == this->food->food.x && this->snake->snake[0].y == this->food->food.y;
}

bool Game::checkCoordinate()
{
   for (int i = 0; i < this->snake->snake.size(); i++)
   {
       if (this->snake->snake[i].x == this->food->food.x && this->snake->snake[i].y == this->food->food.y)
       {
           return false;
       }
   }
   return true;
}
void Game::addFood()
{
        srand(time(0));
        vector <int> pos_X;
        vector <int> pos_Y;
        for(int i = 20; i < SCREEN_WIDTH - 200; i+=20)
        {
            pos_X.push_back(i);
        }
        for(int i = 20; i < SCREEN_HEIGHT - 20; i+=20)
        {
            pos_Y.push_back(i);
        }
        int randX = rand() % pos_X.size();
        int randY = rand() % pos_Y.size();
        this->food->food.x = pos_X[randX];
	    this->food->food.y = pos_Y[randY];
}


void Game::resetClassic()
{
    if (classic_score_val > this->checkClassicHighScore())
    {
        this->setClassicHighScore(classic_score_val);
    }
    this->classic_score_val = 0;
    this->snake->snake.erase(this->snake->snake.begin()+4,this->snake->snake.end());
    this->snake->snake[0].x = SCREEN_WIDTH/2;
    this->snake->snake[0].y = SCREEN_HEIGHT/2;
    this->food->food.x = 100;
    this->food->food.y = 100;
    this->snake->direction = 1;
    return;
}

void Game::resetModern()
{
    if (modern_score_val > this->checkModernHighScore())
    {
        this->setModernHighScore(modern_score_val);
    }
    this->modern_score_val = 0;
    this->snake->snake.erase(this->snake->snake.begin()+4,this->snake->snake.end());
    this->snake->snake[0].x = SCREEN_WIDTH/2;
    this->snake->snake[0].y = SCREEN_HEIGHT/2;
    this->food->food.x = 100;
    this->food->food.y = 100;
    this->snake->direction = 1;
    return;
}


void Game::close() {

    //Delete game objects
    delete(this->interface);
    delete(this->food);
    delete(this->snake);
    delete(this->menu);
    delete(this->text);

	//Destroy window
	SDL_DestroyRenderer( this->gRenderer );
	SDL_DestroyWindow( this->gWindow );
	gWindow = NULL;
	gRenderer = NULL;
	gMusic = NULL;

	//Free audio and text
	Mix_FreeMusic( gMusic );
	TTF_CloseFont( TextTexture1 );
	TTF_CloseFont( TextTexture2 );
	TTF_CloseFont( TextTexture3 );

    //Quit SDL subsystems
	Mix_Quit();
	IMG_Quit();
	SDL_Quit();

    return;
}

bool Game::run() {

    bool quit = false;

    bool modern = false;

    bool classic = false;

    bool game_mode = false;

    bool game_over = false;

    //Declaration of text methods using in game
    TextObject score;
    score.set_color(TextObject::White_Text);

    TextObject text1;
    text1.set_color(TextObject::Red_Text);

    TextObject game_mode1;
    game_mode1.set_color(TextObject::White_Text);

    TextObject game_mode2;
    game_mode2.set_color(TextObject::White_Text);

    TextObject quit_slection1;
    quit_slection1.set_color(TextObject::Black_Text);

    TextObject quit_slection2;
    quit_slection2.set_color(TextObject::Black_Text);

    TextObject best_score;
    best_score.set_color(TextObject::White_Text);

    TextObject int_classic_score;
    int_classic_score.set_color(TextObject::Red_Text);

    TextObject int_modern_score;
    int_modern_score.set_color(TextObject::Red_Text);

    TextObject classic_text;
    classic_text.set_color(TextObject::White_Text);

    TextObject modern_text;
    modern_text.set_color(TextObject::White_Text);

    string score_txt = "Your score";
    text1.SetText(score_txt);
    text1.LoadFromRenderText(TextTexture1,gRenderer);

    string mode1 = "Classic";
    string mode2 = "Modern";
    game_mode1.SetText(mode1);
    game_mode1.LoadFromRenderText(TextTexture2,gRenderer);
    game_mode2.SetText(mode2);
    game_mode2.LoadFromRenderText(TextTexture2,gRenderer);

    string slection1 = "Play Again";
    string slection2 = "Quit";
    quit_slection1.SetText(slection1);
    quit_slection1.LoadFromRenderText(TextTexture2,gRenderer);
    quit_slection2.SetText(slection2);
    quit_slection2.LoadFromRenderText(TextTexture2,gRenderer);

    string best_text = "BEST SCORE:";
    best_score.SetText(best_text);
    best_score.LoadFromRenderText(TextTexture2,gRenderer);

    string classic_score = to_string(this->checkClassicHighScore());
    int_classic_score.SetText(classic_score);
    int_classic_score.LoadFromRenderText(TextTexture2,gRenderer);

    string modern_score = to_string(this->checkModernHighScore());
    int_modern_score.SetText(modern_score);
    int_modern_score.LoadFromRenderText(TextTexture2,gRenderer);

    string classic_txt = "CLASSIC: ";
    classic_text.SetText(classic_txt);
    classic_text.LoadFromRenderText(TextTexture2,gRenderer);

    string modern_txt = "MODERN: ";
    modern_text.SetText(modern_txt);
    modern_text.LoadFromRenderText(TextTexture2,gRenderer);

    //Event handler
    SDL_Event e;
    //Name tag to call if user want to play again
    menu:
        this->playMusic(gMusic);
        this->menu->renderCurrent(this->gRenderer);
        SDL_RenderPresent(gRenderer);
    while(!quit)
    {
        while( SDL_PollEvent( &e ) != 0 )
        {
             bool back = true;

             bool inside = true;

             bool credit = true;

             bool high_score = true;
             if( e.type == SDL_MOUSEMOTION || e.type == SDL_MOUSEBUTTONDOWN || e.type == SDL_MOUSEBUTTONUP )
             {
                //Get mouse position
                int x, y;
                SDL_GetMouseState( &x, &y );


                //Check if mouse is inside the button or not ?
                if( x < 80 || x > 80 + BUTTON_WIDTH || y < SCREEN_HEIGHT/2 - 100 || y > SCREEN_HEIGHT/2 - 20 )
                {
                    inside = false;
                }
                if( x < 80 || x > 80 + BUTTON_WIDTH || y < SCREEN_HEIGHT/2 - 20  || y > SCREEN_HEIGHT/2 + 30 )
                {
                    high_score = false;
                }
                if( x < 80 || x > 80 + BUTTON_WIDTH || y < SCREEN_HEIGHT/2 + 30  || y > SCREEN_HEIGHT/2 + 110)
                {
                    credit = false;
                }
                if (credit)
                {
                    if (e.type == SDL_MOUSEBUTTONDOWN)
                    {
                       back = true;
                       Mix_PlayChannel(-1,gButton_Click,0);
                       this->interface->renderCredit(this->gRenderer);
                       SDL_RenderPresent(gRenderer);
                    }
                }
                if (high_score)
                {
                    if (e.type == SDL_MOUSEBUTTONDOWN)
                    {
                       back = true;
                       Mix_PlayChannel(-1,gButton_Click,0);
                       this->interface->renderPlayGround(this->gRenderer);
                       best_score.RenderText(gRenderer,SCREEN_WIDTH/2-300,100);
                       classic_text.RenderText(gRenderer,100,SCREEN_HEIGHT/2 - 100);
                       modern_text.RenderText(gRenderer,100,SCREEN_HEIGHT/2);
                       int_classic_score.RenderText(gRenderer,SCREEN_WIDTH/2,SCREEN_HEIGHT/2 - 100);
                       int_modern_score.RenderText(gRenderer,SCREEN_WIDTH/2 + 20,SCREEN_HEIGHT/2);
                       SDL_RenderPresent(gRenderer);
                    }

                }
                if (inside)
                {
                    if (e.type == SDL_MOUSEBUTTONDOWN)
                    {
                       Mix_PlayChannel(-1,gButton_Click,0);
                       game_mode = true;
                    }
                }
                if (game_mode)
                {
                    Mix_PauseMusic();
                    game_mode1.RenderText(gRenderer,SCREEN_WIDTH/2-100,SCREEN_HEIGHT/2-100);
                    game_mode2.RenderText(gRenderer,SCREEN_WIDTH/2-100,SCREEN_HEIGHT/2);
                    SDL_RenderPresent(gRenderer);

                    bool focus_classic = true;
                    bool focus_modern = true;
                    if( x < SCREEN_WIDTH/2-100 ||  x > SCREEN_WIDTH/2 - 100 + BUTTON_WIDTH || y < SCREEN_HEIGHT/2 - 100 || y > SCREEN_HEIGHT/2 )
                    {
                        focus_classic = false;
                    }
                    if( x < SCREEN_WIDTH/2-100 ||  x > SCREEN_WIDTH/2 - 100 + BUTTON_WIDTH || y < SCREEN_HEIGHT/2 || y > SCREEN_HEIGHT/2 + BUTTON_HEIGHT )
                    {
                        focus_modern = false;
                    }
                    if (focus_classic)
                    {
                       if (e.type == SDL_MOUSEBUTTONDOWN)
                       {
                           Mix_PlayChannel(-1,gButton_Click,0);
                           classic = true;
                           game_mode = false;
                       }
                    }
                    if (focus_modern)
                    {
                       if (e.type == SDL_MOUSEBUTTONDOWN)
                       {
                           Mix_PlayChannel(-1,gButton_Click,0);
                           modern = true;
                           game_mode = false;
                       }
                    }
                }
            }
            if( e.type == SDL_KEYDOWN && e.key.repeat == 0 )
            {
                  if (e.key.keysym.sym == SDLK_q)
                  {
                      quit = true;
                  }
                  if (back)
                  {
                    if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
                    {
                        if (e.key.keysym.sym == SDLK_b)
                        {
                            credit = false;
                            goto menu;
                        }
                    }
                  }
            }
            while (classic)
            {
                    srand(time(0));
                    while( SDL_PollEvent( &e ) != 0 )
                    {
                                //User requests quit
                        if( e.type == SDL_QUIT )
                        {
                            quit = true;
                        }

                        this->snake->handleEvent(e,gButton_Click);

                    }

                    this->snake->classic();

                    if (this->eatFood())
                    {
                        Mix_PlayChannel(-1,gEat_Effect,0);
                        this->snake->growing();
                        classic_score_val+= 20;
                       do
                       {
                           this->addFood();
                       }
                       while (this->checkCoordinate()==false);
                    }
                    if(this->snake->isHitWall() || this->snake->isBiteSelf() == true )
                    {
                        Mix_PlayChannel(-1,gHit_Effect,0);
                        SDL_Delay(1000);
                        this->interface->renderGameOver(this->gRenderer);
                        SDL_Delay(5000);
                        classic = false;
                        game_over = true;
                    }
                    this->interface->renderPlayGround(this->gRenderer);
                    this->interface->renderWall(this->gRenderer);
                    this->food->renderCurrent(this->gRenderer);
                    this->snake->renderSnake(this->gRenderer);
                    string str_score = to_string(classic_score_val);
                    score.SetText(str_score);
                    score.LoadFromRenderText(TextTexture1,gRenderer);
                    if(classic_score_val < 100)
                    {
                      score.RenderText(gRenderer,700,SCREEN_HEIGHT/2-50);
                    }
                    else if (classic_score_val >= 100 && classic_score_val < 1000)
                    {
                      score.RenderText(gRenderer,690,SCREEN_HEIGHT/2-50);
                    }
                    else
                    {
                      score.RenderText(gRenderer,680,SCREEN_HEIGHT/2-50);
                    }
                    text1.RenderText(gRenderer,640,SCREEN_HEIGHT/2-100);

                    SDL_RenderPresent(gRenderer);

                    SDL_Delay(50);
        }

        while (modern)
        {
                srand(time(0));
                while( SDL_PollEvent( &e ) != 0 )
                {
                    if( e.type == SDL_QUIT )
                    {
                        quit = true;
                    }

                    this->snake->handleEvent(e,gButton_Click);

                }

                this->snake->modern();

                if (this->eatFood())
                {
                    Mix_PlayChannel(-1,gEat_Effect,0);
                    this->snake->growing();
                    modern_score_val+=50;
                    do
                    {
                        this->addFood();
                    }
                    while (this->checkCoordinate()==false);
                }
                /*
                if (this->snake->isBiteSelf() == false)
                {
                    Mix_PlayChannel(-1,gHit_Effect,0);
                    SDL_Delay(1000);
                    //this->interface->renderGameOver(this->gRenderer);
                    SDL_Delay(5000);
                    modern = false;
                    game_over = true;
                }
                */
                if( this->snake->isBiteSelf() == true )
                    {
                        Mix_PlayChannel(-1,gHit_Effect,0);
                        SDL_Delay(1000);
                        this->interface->renderGameOver(this->gRenderer);
                        SDL_Delay(5000);
                        modern = false;
                        game_over = true;
                    }
                this->interface->renderPlayGround(this->gRenderer);
                this->food->renderCurrent(this->gRenderer);
                this->snake->renderSnake(this->gRenderer);
                string str_score = to_string(modern_score_val);
                score.SetText(str_score);
                score.LoadFromRenderText(TextTexture1,gRenderer);
                if(modern_score_val < 100)
                {
                  score.RenderText(gRenderer,700,SCREEN_HEIGHT/2-50);
                }
                else if (modern_score_val >= 100 && modern_score_val < 1000)
                {
                  score.RenderText(gRenderer,690,SCREEN_HEIGHT/2-50);
                }
                else
                {
                  score.RenderText(gRenderer,680,SCREEN_HEIGHT/2-50);
                }
                text1.RenderText(gRenderer,640,SCREEN_HEIGHT/2-100);
                SDL_RenderPresent(gRenderer);

                SDL_Delay(50);
        }
        if (game_over)
        {
            quit_slection1.RenderText(gRenderer,SCREEN_WIDTH/2-150,SCREEN_HEIGHT/2-100);
            quit_slection2.RenderText(gRenderer,SCREEN_WIDTH/2-150,SCREEN_HEIGHT/2);
            SDL_RenderPresent(gRenderer);
            while( SDL_PollEvent( &e ) != 0 )
            {
                if( e.type == SDL_MOUSEMOTION || e.type == SDL_MOUSEBUTTONDOWN || e.type == SDL_MOUSEBUTTONUP )
                {
                    //Get mouse position
                    int x, y;
                    SDL_GetMouseState( &x, &y );
                    bool inside_slection1 = true;
                    bool inside_slection2 = true;
                    if (x < SCREEN_WIDTH/2 - 200 || x > SCREEN_WIDTH/2 + 200 || y < SCREEN_HEIGHT/2 - 150 || y > SCREEN_HEIGHT/2-50)
                    {
                        inside_slection1 = false;
                    }
                    if (x < SCREEN_WIDTH/2 - 200 || x > SCREEN_WIDTH/2 + 200 || y < SCREEN_HEIGHT/2 - 50  || y > SCREEN_HEIGHT/2 + 150)
                    {
                        inside_slection2 = false;
                    }
                    if (inside_slection1)
                    {
                       if (e.type == SDL_MOUSEBUTTONDOWN)
                       {
                           Mix_PlayChannel(-1,gButton_Click,0);
                           this->resetClassic();
                           this->resetModern();
                           game_over = false;
                           goto menu;
                       }
                    }
                    if (inside_slection2)
                    {
                       if (e.type == SDL_MOUSEBUTTONDOWN)
                       {
                           this->resetClassic();
                           this->resetModern();
                           Mix_PlayChannel(-1,gButton_Click,0);
                           quit = true;
                       }
                    }
                }
            }
        }
      }
    }
    this->close();

    return true;
}

int Game::checkClassicHighScore()
{
   ifstream file("./highscore/classic_highscore.txt");
   int cls_scr;
   if (file.is_open())
   {
       file >> cls_scr;
   }
   else
   {
       cout <<"Unable to open file text";
   }
   file.close();

   return cls_scr;
}

int Game::checkModernHighScore()
{
   ifstream file("./highscore/modern_highscore.txt");
   int mdr_scr;
   if (file.is_open())
   {
       file >> mdr_scr;
   }
   else
   {
       cout <<"Unable to open file text";
   }
   file.close();

   return mdr_scr;
}

void Game::setClassicHighScore(int highscore)
{
    ofstream file;
    file.open("./highscore/classic_highscore.txt");
    if (file.is_open())
    {
        file << highscore;
    }
    else
     {
       cout <<"Unable to open file text";
   }
   file.close();

}

void Game::setModernHighScore(int highscore)
{
    ofstream file;
    file.open("./highscore/modern_highscore.txt");
    if (file.is_open())
    {
        file << highscore;
    }
    else
     {
       cout <<"Unable to open file text";
   }
   file.close();

}






