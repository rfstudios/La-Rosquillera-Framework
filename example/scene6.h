#ifndef SCENE6_H
#define SCENE6_H

#include "background.h"
#include "rf_process.h"
#include "rf_engine.h"

class BezierLetter : public RF_Process
{
    public:
        BezierLetter(string txt, Vector2<int> pos, int retardo = 0):RF_Process("BezierLetter")
        {
            position = pos;
            text = txt;
            step+=retardo;
        }
        virtual ~BezierLetter(){
            if(-1 < textID && NULL != RF_Engine::instance->textSources[textID])
            {
                RF_Engine::instance->deleteText(textID);
            }
        }

        virtual void Update();

    private:
        Vector2<int> position;
        string text = "";
        int textID = -1;
        float deltaCount = 0.0f;
        int step = 100;
        int x = -40,y = -60;
};

class Scene6 : public RF_Process
{
    public:
        Scene6():RF_Process("Scene6"){}
        virtual ~Scene6(){}

        virtual void Start();
        virtual void Update();

        void bezierText(string text, int y);

    private:
        background* bg;
        float deltaCount = 0.0f;
        int step = 0, step2 = 0, cuentatexto = 0;
};

#endif // SCENE6_H
