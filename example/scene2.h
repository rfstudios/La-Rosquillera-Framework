#ifndef SCENE2_H
#define SCENE2_H

#include "rf_background.h"
#include "rf_process.h"
#include "rf_engine.h"

#include <vector>
using namespace std;

class Scene2 : public RF_Process
{
    public:
        Scene2():RF_Process("Scene2"){}
        virtual ~Scene2();

        virtual void Start();
        virtual void Update();

    private:
        RF_Background* bg;
        Uint32 bgImg[640][480];
        float deltacount=0.0f;
        Transform2D<int> t;
};

#endif // SCENE2_H
