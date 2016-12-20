#ifndef SCENE1_H
#define SCENE1_H

#include "rf_background.h"
#include "rf_process.h"
#include "rf_engine.h"

class Scene1 : public RF_Process
{
    public:
        Scene1():RF_Process("Scene1"){}
        virtual ~Scene1(){}

        virtual void Start();
        virtual void Update();

    private:
        SDL_Surface* bgImg;

        void setBar(int x, int width, bool black = false);
        void getBar(int x, int width);
        void revolveChanels(int mod = 0);

        float deltaCont = 0.5f;
        int colPos[5] = {0,128,256,384,512}, nextX;
};

#endif // SCENE1_H
