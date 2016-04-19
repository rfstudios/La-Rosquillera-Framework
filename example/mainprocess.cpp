/*
  LA ROSQUILLERA FRAMEWORK
  Copyright (C) 2015 Yawin <tuzmakel@gmail.com>

  This is an example of videogame. You can use as the fuck you want.
*/

#include "mainprocess.h"
#include "execontrol.h"
#include <SDL2/SDL_ttf.h>

mainProcess::~mainProcess(){}

void mainProcess::Start()
{
    engine->newTask(new exeControl(),id);
    engine->playSong("resources/st7.wav");

    prepareSurface();

    for(int i = 0; i < engine->ventana->width(); i++)
    {
        for(int j = 0; j < engine->ventana->height(); j++)
        {
            putPixel(i,j,0xffffff);
        }
    }
    return;
}
void mainProcess::Update()
{
    //generateTexture();
    return;
}
void mainProcess::putPixel(int x, int y, Uint32 pixel){
    int bpp = screen->format->BytesPerPixel;
    engine->Debug(bpp);

    /* Here p is the address to the pixel we want to set */
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
}
void mainProcess::prepareSurface(){
    screen = SDL_CreateRGBSurface(0,engine->ventana->width(), engine->ventana->height(),32,0,0,0,0);
}
void mainProcess::generateTexture(){
    graph = SDL_CreateTextureFromSurface(engine->ventana->renderer, screen);
}
void mainProcess::clearSurface(){}
