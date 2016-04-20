#ifndef BACKGROUND_H
#define BACKGROUND_H

#include "rf_process.h"


class background : public RF_Process
{
    public:
        background():RF_Process("Background"){}
        virtual ~background(){}

        virtual void Update();

        Uint32 getPixel(int x, int y);
        void putPixel(int x, int y, Uint32 pixel);
        void prepareSurface();
        void generateTexture();
        void clearSurface(Uint32 color = 0);

    private:
        SDL_Surface* screen;
        bool needGenerate = false;
};

#endif // BACKGROUND_H
