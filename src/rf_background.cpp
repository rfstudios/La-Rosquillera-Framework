#include "rf_background.h"
#include "rf_primitive.h"

RF_Background* RF_Background::instance = NULL;
void RF_Background::LateDraw(){
    generateTexture();
    return;
}
Uint32 RF_Background::getPixel(int x, int y){
    return RF_Primitive::getPixel(screen, x, y);
}
void RF_Background::putPixel(int x, int y, Uint32 pixel){
    RF_Primitive::putPixel(screen, x, y, pixel);
    needGenerate = true;
}
void RF_Background::prepareSurface(){
    if(screen != NULL){SDL_FreeSurface(screen);}
    screen = SDL_CreateRGBSurface(0,RF_Engine::instance->ventana->width(), RF_Engine::instance->ventana->height(),32,0,0,0,0);
}
void RF_Background::generateTexture(){
    if(!needGenerate){return;}
    if(NULL == screen){return;}
    needGenerate = false;
    SDL_DestroyTexture(graph);
    graph = SDL_CreateTextureFromSurface(RF_Engine::instance->ventana->renderer, screen);
}
void RF_Background::clearSurface(Uint32 color){
    for(int i = 0; i < RF_Engine::instance->ventana->width(); i+=3)
    {
        for(int j = 0; j < RF_Engine::instance->ventana->height(); j+=3)
        {
            putPixel(i,j,color);    putPixel(i,j+1,color);    putPixel(i,j+2,color);
            putPixel(i+1,j,color);  putPixel(i+1,j+1,color);  putPixel(i+1,j+2,color);
            putPixel(i+2,j,color);  putPixel(i+2,j+1,color);  putPixel(i+2,j+2,color);
        }
    }
    needGenerate = true;
}
void RF_Background::addSurface(SDL_Surface *tmpSrf){
    for(int i=0;i<tmpSrf->w;i++)
    {
        for(int j=0;j<tmpSrf->h;j++)
        {
            Uint32 tmpC = RF_Primitive::getPixel(tmpSrf,i,j);

            if(0x000000 != tmpC)
            {
                putPixel(i,j,tmpC);
                needGenerate = true;
            }
        }
    }
}
