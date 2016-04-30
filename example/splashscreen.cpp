#include "splashscreen.h"
#include "mainprocess.h"
#include "rf_primitive.h"

void SplashScreen::Start()
{
    srand (RF_Engine::instance->time->currentTime);
    bgImg = RF_Engine::instance->loadPNG_Surface("resources/gfx/logo.png");
    bg = dynamic_cast<mainProcess*>(RF_Engine::instance->taskManager[father])->bg;
    bg->clearSurface(0xffffff);
    step = 0;
}

void SplashScreen::Update()
{
    deltaCont += RF_Engine::instance->time->deltaTime;
    if(0.025 <= deltaCont)
    {
        deltaCont = 0.0f;

        step++;

        int stp = step;
        if(50 <= stp){stp = 50;}

        bg->clearSurface(0xffffff);
        for(int i = 0; i < bgImg->w; i++)
        {
            for(int j = 0; j < bgImg->h; j++)
            {
                int xx = i - (5 * ( (rand()%30) - 15 ) - 5) * (50-stp);
                int yy = j - (5 * ( (rand()%30) - 15 ) - 5) * (50-stp);

                if(0 <= xx && 0 <= yy && bgImg->w > xx && bgImg->h > yy)
                {
                    bg->putPixel(xx,yy,RF_Primitive::getPixel(bgImg,i,j));
                }
            }
        }

        if(150 <= step)
        {
            bg->clearSurface(0x000000);
            dynamic_cast<mainProcess*>(RF_Engine::instance->taskManager[father])->state() = 1;
        }
    }
}

SplashScreen::~SplashScreen()
{
    SDL_FreeSurface(bgImg);
}
