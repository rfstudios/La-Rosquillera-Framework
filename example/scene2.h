#ifndef SCENE2_H
#define SCENE2_H

#include "background.h"
#include "rf_process.h"
#include "rf_engine.h"

#include <vector>
using namespace std;

class scrLetra : public RF_Process
{
    public:
        scrLetra(string text, Vector2<int> StartPosition):RF_Process("scrLetra"){
            txt=text;
            pos.x = (float)StartPosition.x;
            pos.y = (float)StartPosition.y;
        }

        virtual ~scrLetra(){
            if(-1 < textID && NULL != RF_Engine::instance->textSources[textID])
            {
                RF_Engine::instance->deleteText(textID);
            }
        }

        virtual void Update();

    private:
        int textID = -1;
        string txt="";

        Vector2<float> pos;
};

class Scene2 : public RF_Process
{
    public:
        Scene2():RF_Process("Scene2"){}
        virtual ~Scene2(){}

        virtual void Start();
        virtual void Update();

        bool Starfield(int limit);
        void Scrolltext(string text, int y);

    private:
        background* bg;
        vector<Vector2<int>> stars;
        vector<int> stars_speed;

        float deltaCount = 0.0f;
        bool lastFrame = false, cH = false;
        int step=0, step2=0, cuentaobj=0, objtorend = 0, textcont=0;
};

#endif // SCENE2_H
