#include "rf_background.h"
#include "rf_primitive.h"

RF_Background* RF_Background::instance = NULL;
void RF_Background::Update()
{
    generateTexture();
    return;
}

Uint32 RF_Background::getPixel(int x, int y){
    int bpp = screen->format->BytesPerPixel;
    /* Here p is the address to the pixel we want to retrieve */
    Uint8 *p = (Uint8 *)screen->pixels + y * screen->pitch + x * bpp;

    switch(bpp) {
    case 1:
        return *p;
        break;

    case 2:
        return *(Uint16 *)p;
        break;

    case 3:
        if(SDL_BYTEORDER == SDL_BIG_ENDIAN)
            return p[0] << 16 | p[1] << 8 | p[2];
        else
            return p[0] | p[1] << 8 | p[2] << 16;
        break;

    case 4:
        return *(Uint32 *)p;
        break;

    default:
        return 0;       /* shouldn't happen, but avoids warnings */
    }
}
void RF_Background::putPixel(int x, int y, Uint32 pixel){
    if(0 > x || 0 > y || screen->w <= x || screen->h <= y){return;}

    int bpp = screen->format->BytesPerPixel;
    Uint8 *p = (Uint8 *)screen->pixels + y * screen->pitch + x * bpp;

    switch(bpp) {
    case 1:
        *p = pixel;
        break;

    case 2:
        *(Uint16 *)p = pixel;
        break;

    case 3:
        if(SDL_BYTEORDER == SDL_BIG_ENDIAN) {
            p[0] = (pixel >> 16) & 0xff;
            p[1] = (pixel >> 8) & 0xff;
            p[2] = pixel & 0xff;
        } else {
            p[0] = pixel & 0xff;
            p[1] = (pixel >> 8) & 0xff;
            p[2] = (pixel >> 16) & 0xff;
        }
        break;

    case 4:
        *(Uint32 *)p = pixel;
        break;
    }

    needGenerate = true;
}
void RF_Background::prepareSurface(){
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
