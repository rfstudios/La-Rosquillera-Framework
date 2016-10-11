#ifndef SPLASHSCREEN_H
#define SPLASHSCREEN_H

#include "rf_process.h"
#include "rf_engine.h"
#include "rf_background.h"

class SplashScreen : public RF_Process
{
    public:
        SplashScreen():RF_Process("SplashScreen"){};
        virtual ~SplashScreen();

        virtual void Start();
        virtual void Update();

    private:
        SDL_Surface* bgImg;
        RF_Background* bg;

        float deltaCont = 0.0f, tempPause = 3.0;
        int step;
        int w,h;
};

#endif // SPLASHSCREEN_H
