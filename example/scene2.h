#ifndef SCENE2_H
#define SCENE2_H

#include "rf_background.h"
#include "rf_process.h"
#include "rf_engine.h"
#include "rf_parallax.h"

#include <vector>
using namespace std;

class Scene2 : public RF_Process
{
    public:
        Scene2():RF_Process("Scene2"){}
        virtual ~Scene2(){}

        virtual void Start();
        virtual void Update();

        void metabolas();
        float metang;
        Vector2<int> b1, b2, b3;
        int i,j;

    private:
        RF_Background* bg;
        float deltacount=0.0f;
        RF_Parallax* pL;
};

#endif // SCENE2_H
