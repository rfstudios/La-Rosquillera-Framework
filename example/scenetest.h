#ifndef SCENETEST_H
#define SCENETEST_H

#include "rf_background.h"
#include "rf_process.h"
#include "rf_engine.h"
#include "rf_primitive.h"
#include "rf_parallax_layer.h"
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

    private:
        float deltacount = 0.0f;
        int cont = 0, assetCont;
        RF_Background* bg;
};

#endif // SCENETEST_H
