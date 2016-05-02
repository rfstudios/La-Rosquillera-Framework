#ifndef SCENE3_H
#define SCENE3_H

#include "rf_process.h"
#include "rf_engine.h"
#include "background.h"

#include <math.h>
#include <vector>
using namespace std;

class Scene3 : public RF_Process
{
    public:
        Scene3():RF_Process("Scene3"){}
        virtual ~Scene3(){}

        virtual void Start();
        virtual void Update();

        void metaballs(int type = 0);

    private:
        Uint32 bgImg[640][480];
        Uint32 bgImg2[640][480];
        background* bg;
        int step = 0;

        float deltaCont = 0, ballC = 1;
};

#endif // SCENE3_H
