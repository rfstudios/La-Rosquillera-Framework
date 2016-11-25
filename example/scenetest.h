#ifndef SCENETEST_H
#define SCENETEST_H

#include "rf_background.h"
#include "rf_process.h"
#include "rf_engine.h"
#include "rf_primitive.h"
#include "rf_parallax.h"
#include "mainprocess.h"

#include <vector>
using namespace std;

class SceneTest : public RF_Process
{
    public:
        SceneTest():RF_Process("SceneTest"){}
        virtual ~SceneTest(){}

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

        int step = 0;
        int metarange;
};

#endif // SCENETEST_H
