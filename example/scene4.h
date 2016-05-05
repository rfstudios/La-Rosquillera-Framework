#ifndef SCENE4_H
#define SCENE4_H

#include "rf_process.h"
#include "rf_engine.h"
#include "background.h"

#include <math.h>
using namespace std;

class Scene4 : public RF_Process
{
    public:
        Scene4():RF_Process("Scene4"){}
        virtual ~Scene4(){}

        virtual void Start();
        virtual void Update();

    private:
        background* bg;
        Uint32 bgImg[640][480], bgImg2[640][480];
        int step = 0, contB = 0;
        float deltacount = 0.0f;
};

#endif // SCENE4_H
