#include "scene5.h"

#include "mainprocess.h"
#include <string>
using namespace std;

void Scene5::Start(){
    RF_Engine::instance->font = TTF_OpenFont("resources/Times_New_Roman.ttf", 30);
    bg = dynamic_cast<mainProcess*>(RF_Engine::instance->taskManager[father])->bg;
}

void Scene5::Update(){
    if(16800 > RF_Engine::instance->time->fixedCTime())
    {
        if(textCont<3)
        {
            RF_Engine::instance->newTask(new puntoVessel(),id);
        }

        deltaCount += RF_Engine::instance->time->deltaTime;
        if(0.025 < deltaCount)
        {
            bg->clearSurface();
            if(79 == step%80)
            {
                switch(textCont)
                {
                    case 0:
                        creaTexto("NEtbuRNER", Vector2<int>(320,360));
                        break;
                    case 1:
                        creaTexto("Ham - SFL", Vector2<int>(220,360));
                        break;
                    case 2:
                        creaTexto("Debvgger", Vector2<int>(420,360));
                        break;
                    case 3:
                        creaTexto("Aki", Vector2<int>(300,360));
                        break;
                    case 4:
                        creaTexto("Purple  Studios", Vector2<int>(200,360));
                        break;
                    case 5:
                        creaTexto("Kulebril", Vector2<int>(400,360));
                        break;
                }

                textCont++;
                step=-1;
            }

            step++;
            deltaCount = 0.0f;
        }
    }
    else
    {
        bg->clearSurface();
        dynamic_cast<mainProcess*>(RF_Engine::instance->taskManager[father])->state() = 6;
    }
}

void Scene5::creaTexto(string txt, Vector2<int> p){
    int posX = 0;
    for(int i = 0; i < txt.length(); i++)
    {
        if(0<i)
        {
            if(txt.substr(i-1,1) == "l")
            {
                posX-=10;
            }
            else if(txt.substr(i-1,1) == "H")
            {
                posX+=2;
            }
            else if(txt.substr(i-1,1) == "a")
            {
                posX-=4;
            }
            else if(txt.substr(i-1,1) == "R")
            {
                posX-=2;
            }
            else if(txt.substr(i-1,1) == "u")
            {
                posX-=2;
            }
            else if(txt.substr(i-1,1) == "b")
            {
                posX-=4;
            }
            else if(txt.substr(i-1,1) == "t")
            {
                posX-=10;
            }
            else if(txt.substr(i-1,1) == "S")
            {
                posX-=2;
            }
            else if(txt.substr(i-1,1) == "F")
            {
                posX-=2;
            }
            else if(txt.substr(i-1,1) == " ")
            {
                posX-=15;
            }
            else if(txt.substr(i-1,1) == "m")
            {
                posX+=10;
            }
            else if(txt.substr(i-1,1) == "D")
            {
                posX+=3;
            }
            else if(txt.substr(i-1,1) == "e")
            {
                posX-=6;
            }
            else if(txt.substr(i-1,1) == "r")
            {
                posX-=8;
            }
            else if(txt.substr(i-1,1) == "v")
            {
                posX-=4;
            }
            else if(txt.substr(i-1,1) == "p")
            {
                posX-=4;
            }
            else if(txt.substr(i-1,1) == "g")
            {
                posX-=5;
            }
            else if(txt.substr(i-1,1) == "d")
            {
                posX-=2;
            }
            else if(txt.substr(i-1,1) == "o")
            {
                posX-=2;
            }
            else if(txt.substr(i-1,1) == "i")
            {
                posX-=12;
            }
            else if(txt.substr(i-1,1) == "k")
            {
                posX-=3;
            }
        }

        RF_Engine::instance->newTask(new aleatLetra(txt.substr(i,1),Vector2<int>(p.x+posX,p.y), 20, 15), id);
        posX+=20;
    }
}

void puntoVessel::Start(){
    fScene = dynamic_cast<Scene5*>(RF_Engine::instance->taskManager[father]);
    vida = RF_Engine::instance->time->fixedCTime() + 10000;
}
void puntoVessel::Update(){
    if(RF_Engine::instance->time->fixedCTime() < vida)
    {
        int x = 320 + sin(M_PI*((vida + RF_Engine::instance->time->fixedCTime())*1.2)*0.00016)*300;
        int y = 120 + sin(M_PI*((vida + RF_Engine::instance->time->fixedCTime())*1.2)*5*0.0005) * 100;
        fScene->bg->putPixel(x,y, 0xffffff);
        fScene->bg->putPixel(x,y+1, 0xffffff);
        fScene->bg->putPixel(x+1,y, 0xffffff);
        fScene->bg->putPixel(x+1,y+1, 0xffffff);
    }
}

void aleatLetra::Start(){
    fScene = dynamic_cast<Scene5*>(RF_Engine::instance->taskManager[father]);
}
void aleatLetra::Update(){
    if(-1 < textID && NULL != RF_Engine::instance->textSources[textID])
    {
        RF_Engine::instance->deleteText(textID);
    }

    Vector2<int> p;
    int st = _steps - fScene->step;

    if(0 >= st)
    {
        if(0 < (_steps + sC) - fScene->step)
        {
            st = 0;
        }
        else if(-(_steps) < (_steps + sC) - fScene->step)
        {
            st = (_steps + sC) - fScene->step;
        }
        else
        {
            signal = S_KILL;
        }
    }

    p.x = (int)pos.x + (rand()%50 - 25) * st;
    p.y = (int)pos.y + (rand()%50 - 25) * st;
    textID = RF_Engine::instance->write(txt, {255,255,255}, p);

    if(-10 > pos.x){signal = S_KILL;}
}
