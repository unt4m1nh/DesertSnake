#include "BaseObj.h"

BaseOject::BaseOject(){
    p_object_=NULL;
    rect_.h=0;
    rect_.w=0;
    rect_.x=0;
    rect_.y=0;
}

BaseOject::~BaseOject()
{
    Free();
}

void BaseOject::Render(SDL_Renderer* des,const SDL_Rect* clip  )
{
    SDL_Rect renderquad={rect_.x,rect_.y,rect_.w,rect_.h};

    SDL_RenderCopy(des,p_object_,clip,&renderquad);
}

void BaseOject::Free()
{
    if(p_object_!=NULL)
    {
        SDL_DestroyTexture(p_object_);
        p_object_=NULL;
        rect_.h=0;
        rect_.w=0;
    }


}
