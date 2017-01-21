#ifndef SPLASHSCREEN_H
#define SPLASHSCREEN_H

#include "rf_process.h"
#include "rf_engine.h"

class SplashScreen : public RF_Process
{
    public:
        SplashScreen():RF_Process("SplashScreen"){};
        virtual ~SplashScreen();

        virtual void Start();
        virtual void Update();

    private:
        SDL_Surface* bgImg;

        float deltaCont = 0.0f, tempPause = 1.5;
        int step;
        int w,h;
        bool banned = false;
};

#endif // SPLASHSCREEN_H
