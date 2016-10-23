#include "splashscreen.h"
#include "mainprocess.h"
#include "rf_primitive.h"

void SplashScreen::Start()
{
    RF_Engine::instance->Debug(type);

    srand (RF_Engine::instance->time->currentTime);
    bgImg = RF_Engine::instance->getGfx2DSrf("logo");
    bg = dynamic_cast<mainProcess*>(RF_Engine::instance->taskManager[father])->bg;
    bg->clearSurface(0xffffff);
    step = 0;
}

void SplashScreen::Update()
{
    deltaCont += RF_Engine::instance->time->deltaTime;
    if(tempPause+0.025 <= deltaCont)
    {
        deltaCont = 0.0f;
        tempPause = 0.0;

        step++;

        int stp = step;
        if(50 <= stp){stp = 50;}

        bg->clearSurface(0xffffff);
        for(int i = 0; i < bgImg->w; i+=3)
        {
            for(int j = 0; j < bgImg->h; j+=3)
            {
                int xx = i - ((rand()%30) - 20) * (50-stp);
                int yy = j - ((rand()%30) - 20) * (50-stp);

                if(0 <= xx && 0 <= yy && bgImg->w > xx && bgImg->h > yy)
                {
                    bg->putPixel(xx,yy,RF_Primitive::getPixel(bgImg,i,j));
                    bg->putPixel(xx,yy+1,RF_Primitive::getPixel(bgImg,i,j+1));
                    bg->putPixel(xx,yy+2,RF_Primitive::getPixel(bgImg,i,j+2));

                    bg->putPixel(xx+1,yy,RF_Primitive::getPixel(bgImg,i+1,j));
                    bg->putPixel(xx+1,yy+1,RF_Primitive::getPixel(bgImg,i+1,j+1));
                    bg->putPixel(xx+1,yy+2,RF_Primitive::getPixel(bgImg,i+1,j+2));

                    bg->putPixel(xx+2,yy,RF_Primitive::getPixel(bgImg,i+2,j));
                    bg->putPixel(xx+2,yy+1,RF_Primitive::getPixel(bgImg,i+2,j+1));
                    bg->putPixel(xx+2,yy+2,RF_Primitive::getPixel(bgImg,i+2,j+2));
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
