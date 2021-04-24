#ifndef BASEOBJ_H
#define BASEOBJ_H

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include "LTexture.h"

class BaseOject
{
 public:
     BaseOject();
     ~BaseOject();

     void SetRect(const int& x,const int& y){rect_.x=x,rect_.y=y;}
     SDL_Rect GetRect() const {return rect_;}
     SDL_Texture* GetObject() const {return p_object_;}

     void Render(SDL_Renderer* des,const SDL_Rect* clip=NULL);
     void Free();

 private:
    SDL_Texture* p_object_=NULL;
    SDL_Rect rect_;

};



#endif // BASEOBJ_H
