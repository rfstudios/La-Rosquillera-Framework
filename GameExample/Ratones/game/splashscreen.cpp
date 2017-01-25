#include "splashscreen.h"
#include "mainprocess.h"
#include "rf_primitive.h"
#include "rf_background.h"

void SplashScreen::Start()
{
    RF_Engine::instance->Debug(type);

    srand (RF_Engine::instance->time->currentTime);
    bgImg = RF_Engine::instance->getGfx2DSrf("logo");
    RF_Background::instance->clearSurface(0xffffff);
    step = 0.0;

    w = -320 + RF_Engine::instance->ventana->width() * 0.5;
    h = -240 + RF_Engine::instance->ventana->height() * 0.5;
}

void SplashScreen::Update()
{
    deltaCont += RF_Engine::instance->time->deltaTime;
    if(tempPause <= deltaCont)
    {
        deltaCont = 0.0f;
        tempPause = 0.0;

        step += RF_Engine::instance->time->deltaTime*100;

        int stp = step;
        if(900 <= stp){stp = 900;}

        if(10 > step)
        {
            if(!banned)
            {
                banned = true;
                RF_Background::instance->clearSurface(0xFFFFFF);
                graph = RF_Engine::instance->getGfx2D("banner");

                transform.position.x = 20;
                transform.position.y = (RF_Engine::instance->ventana->height()>>1) - 108;
            }
        }
        else if(550 <= step && 750 > step)
        {
            if(banned)
            {
                banned = false;
                graph = NULL;
            }
        }
        else if(750 <= step && 1000 >= step)
        {
            RF_Background::instance->clearSurface(0xffffff);

            for(int i = 0; i < bgImg->w; i+=3)
            {
                for(int j = 0; j < bgImg->h; j+=3)
                {
                    int xx = i - ((rand()%30) - 20) * (900-stp);
                    int yy = j - ((rand()%30) - 20) * (900-stp);

                    if(0 <= xx && 0 <= yy && bgImg->w > xx && bgImg->h > yy)
                    {
                        RF_Background::instance->putPixel(w + xx, h + yy,RF_Primitive::getPixel(bgImg,i,j));
                        RF_Background::instance->putPixel(w + xx, h + yy+1,RF_Primitive::getPixel(bgImg,i,j+1));
                        RF_Background::instance->putPixel(w + xx, h + yy+2,RF_Primitive::getPixel(bgImg,i,j+2));

                        RF_Background::instance->putPixel(w + xx+1, h + yy,RF_Primitive::getPixel(bgImg,i+1,j));
                        RF_Background::instance->putPixel(w + xx+1, h + yy+1,RF_Primitive::getPixel(bgImg,i+1,j+1));
                        RF_Background::instance->putPixel(w + xx+1, h + yy+2,RF_Primitive::getPixel(bgImg,i+1,j+2));

                        RF_Background::instance->putPixel(w + xx+2, h + yy,RF_Primitive::getPixel(bgImg,i+2,j));
                        RF_Background::instance->putPixel(w + xx+2, h + yy+1,RF_Primitive::getPixel(bgImg,i+2,j+1));
                        RF_Background::instance->putPixel(w + xx+2, h + yy+2,RF_Primitive::getPixel(bgImg,i+2,j+2));
                    }
                }
            }
        }
        else if(1000 < step)
        {
            RF_Background::instance->clearSurface(0x000000);
            dynamic_cast<mainProcess*>(RF_Engine::instance->taskManager[father])->state() = 1;
        }
    }
}

SplashScreen::~SplashScreen()
{
    //SDL_FreeSurface(bgImg);
}
