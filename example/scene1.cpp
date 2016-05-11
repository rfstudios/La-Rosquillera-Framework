#include "scene1.h"
#include "mainprocess.h"
#include "rf_primitive.h"

void Scene1::Start()
{
    RF_Engine::instance->Debug(type);

    srand (RF_Engine::instance->time->currentTime);
    bgImg = RF_Engine::instance->loadPNG_Surface("resources/gfx/demoordie.png");
    bg = dynamic_cast<mainProcess*>(RF_Engine::instance->taskManager[father])->bg;

    for(int i=0; i < bgImg->w; i++)
    {
        for(int j=0; j < bgImg->h; j++)
        {
            bg->putPixel(i,j,RF_Primitive::getPixel(bgImg,i,j));
        }
    }

    nextX = colPos[rand()%5];
}
void Scene1::Update()
{
    if(8950 <= RF_Engine::instance->time->fixedCTime())
    {
        if(17100 > RF_Engine::instance->time->fixedCTime())
        {
            deltaCont+=RF_Engine::instance->time->deltaTime;
            if(0.5 <= deltaCont)
            {
                if(1.02 <= deltaCont)
                {
                    getBar(nextX,128);
                    deltaCont = 0.0;
                    nextX = colPos[rand()%5];
                }
                else
                {
                    setBar(nextX,128);
                }
            }
        }
        else if(34190 > RF_Engine::instance->time->fixedCTime())
        {
            if(-1 < nextX)
            {
                deltaCont = 1.02;
                getBar(nextX,128);
                nextX = -1;
            }

            deltaCont+=RF_Engine::instance->time->deltaTime;
            if(1.02 <= deltaCont)
            {
                revolveChanels();
                deltaCont = 0.0;
            }
        }
        else if(38385 > RF_Engine::instance->time->fixedCTime())
        {
            if(-1 == nextX){nextX = 0;}

            deltaCont+=RF_Engine::instance->time->deltaTime;
            if(0.5 <= deltaCont)
            {
                if(0.75 <= deltaCont)
                {
                    //revolveChanels();
                    setBar(colPos[nextX],128, true);
                    deltaCont = 0.0;
                    nextX++;
                }
            }
        }
        else
        {
            bg->clearSurface(0x000000);
            dynamic_cast<mainProcess*>(RF_Engine::instance->taskManager[father])->state() = 2;
        }
    }
    return;
}

void Scene1::setBar(int x, int width, bool black){
    for(int i = x; i < x + width; i++)
    {
        for(int j=0; j < bgImg->h; j++)
        {
            if(0 <= i && 0 <= j && bgImg->w > i && bgImg->h > j)
            {
                Uint32 tmpC = RF_Primitive::getPixel(bgImg,i,j);
                if(black) tmpC = 0xffffff;

                bg->putPixel(i,j,0xffffff - tmpC);
            }
        }
    }
}
void Scene1::getBar(int x, int width){
    for(int i=x; i < x + width; i++)
    {
        for(int j=0; j < bgImg->h; j++)
        {
            if(0 <= i && 0 <= j && bgImg->w > i && bgImg->h > j)
            {
                bg->putPixel(i,j,RF_Primitive::getPixel(bgImg,i,j));
            }
        }
    }
}
void Scene1::revolveChanels(int mod){
    for(int i=0; i < bgImg->w; i++)
    {
        for(int j=0; j < bgImg->h; j++)
        {
            if(0 <= i && 0 <= j && bgImg->w > i && bgImg->h > j)
            {
                Uint32 tmpC = bg->getPixel(i,j);
                Uint8 r,g,b; SDL_GetRGB(tmpC,bgImg->format,&r,&g,&b);
                int r_mod = (rand()%10) * mod;
                bg->putPixel(i,j,SDL_MapRGB(bgImg->format,255 - (b + r_mod),255 - (r + r_mod),255 - (g + r_mod)));
            }
        }
    }
}

Scene1::~Scene1()
{
    SDL_FreeSurface(bgImg);
}
