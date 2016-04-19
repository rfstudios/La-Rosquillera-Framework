/*
  LA ROSQUILLERA FRAMEWORK
  Copyright (C) 2015 Yawin <tuzmakel@gmail.com>

  This is an example of videogame. You can use as the fuck you want.
*/

#ifndef MAINPROCESS_H
#define MAINPROCESS_H

#include "rf_process.h"

class mainProcess : public RF_Process
{
    public:
        mainProcess():RF_Process("mainProcess"){}
        virtual ~mainProcess();

        virtual void Start();
        virtual void Update();

        void putPixel(int x, int y, Uint32 pixel);
        void prepareSurface();
        void generateTexture();
        void clearSurface();

    private:
        SDL_Surface* screen;
};

#endif // MAINPROCESS_H
