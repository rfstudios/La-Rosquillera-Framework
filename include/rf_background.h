#ifndef RF_BACKGROUND_H
#define RF_BACKGROUND_H

#include "rf_process.h"

class RF_Background : public RF_Process
{
    public:
        static RF_Background* instance;

        RF_Background():RF_Process("RF_Background")
        {
            if(instance != NULL)
            {
                delete this;
            }
            else
            {
                instance = this;
            }
        }

        virtual ~RF_Background()
        {
            SDL_FreeSurface(screen);
        }

        virtual void Start(){zLayer = -1;}
        virtual void LateDraw();

        Uint32 getPixel(int x, int y);
        void putPixel(int x, int y, Uint32 pixel);
        void prepareSurface();
        void generateTexture();
        void clearSurface(Uint32 color = 0);
        void addSurface(SDL_Surface *tmpSrf);

        SDL_Surface* screen = NULL;

    private:
        bool needGenerate = false;
};

#endif // RF_BACKGROUND_H
