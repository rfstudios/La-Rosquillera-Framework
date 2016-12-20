#ifndef SCENE4_H
#define SCENE4_H

#include "rf_process.h"
#include "rf_engine.h"
#include "rf_background.h"

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
        Uint32 bgImg[640][480], bgImg2[640][480];
        int step = 0;
        float deltacount = 0.0f;

        Vector3<int> b1, b2, b3;
        float calcTemp, calci1, calci2, calci3, metang;
        float crZ1, srZ1, sr2Z1, crZ2, srZ2, sr2Z2;
        int x, y, calc12, calc11, calc32, calc21, calc22;
        int xZ1, yZ1, xZ2, yZ2;
};

#endif // SCENE4_H
