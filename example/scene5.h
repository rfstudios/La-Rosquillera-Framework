#ifndef SCENE5_H
#define SCENE5_H

#include "rf_process.h"
#include "rf_engine.h"
#include "background.h"

#include <math.h>
using namespace std;

class Scene5;
class puntoVessel : public RF_Process
{
    public:
        puntoVessel():RF_Process("puntoVessel"){}

        virtual ~puntoVessel(){}

        virtual void Start();
        virtual void Update();

    private:
        int vida = 0;
        Scene5* fScene;
};
class aleatLetra : public RF_Process
{
    public:
        aleatLetra(string text, Vector2<int> StartPosition, int steps = 100, int waitStep = 50):RF_Process("aleatLetra"){
            txt=text;
            pos.x = (float)StartPosition.x;
            pos.y = (float)StartPosition.y;
            _steps = steps;
            sC = waitStep;
        }

        virtual ~aleatLetra(){
            if(-1 < textID && NULL != RF_Engine::instance->textSources[textID])
            {
                RF_Engine::instance->deleteText(textID);
            }
        }

        virtual void Start();
        virtual void Update();

    private:
        int textID = -1;
        string txt="";

        Vector2<float> pos;
        int _steps = 100, sC=0;

        Scene5* fScene;
};

class Scene5 : public RF_Process
{
    public:
        Scene5():RF_Process("Scene5"){}
        virtual ~Scene5(){}

        virtual void Start();
        virtual void Update();

        int step = 0, textCont = 0;
        float deltaCount = 0;
        void creaTexto(string txt, Vector2<int> p);

        background* bg;
};

#endif // SCENE5_H
