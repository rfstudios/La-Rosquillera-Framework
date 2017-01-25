#ifndef MAINPROCESS_H
#define MAINPROCESS_H

#include "rf_process.h"
#include "rf_background.h"

class mainProcess : public RF_Process
{
    public:
        mainProcess():RF_Process("mainProcess"){}
        virtual ~mainProcess();

        virtual void Start();
        virtual void Update();

        RF_Background* bg;

        int& state(){return stateMachine;}

    private:
        int stateMachine = 0;
        int scene;

        Uint32 bgImg[640][480];
        Uint32 bgImg2[640][480];
        float deltacount = 0;
        float metang;
        Vector3<int> b1, b2, b3, b4;
        float radio = 0.80, goo = 0.90, result;
        int mi, mj, mii, mjj, step = 0;

        void breik(RF_Process* escena){}
        void Fantasy();
};

#endif // MAINPROCESS_H
