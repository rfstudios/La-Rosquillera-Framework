#include "mainprocess.h"
#include "execontrol.h"
#include "raton.h"

#include "splashscreen.h"
#include "mainmenu.h"
#include "game.h"
#include "endscene.h"

#include "rf_declares.h"
#include "rf_primitive.h"
#include "rf_soundmanager.h"
#include <SDL2/SDL_ttf.h>

mainProcess::~mainProcess(){}

void mainProcess::Start()
{
    //Levantamos el proceso que detectará, durante toda la ejecución, si pulsamos
    //la tecla esc;
        RF_Engine::instance->newTask(new exeControl(),id);

    //Cargamos recursos
        RF_Engine::instance->loadAsset("resources/common");
        RF_Engine::instance->font = RF_Engine::instance->getFont("Coving01",25);

    scene = RF_Engine::instance->newTask(new SplashScreen(),id);

    //Fantasía
        SDL_Surface* bgImgS = RF_Engine::instance->getGfx2DSrf("world_bg");
        for(int i=0; i<640; i++)
        {
            for(int j=0; j<480; j++)
            {
                bgImg[i][j] = RF_Primitive::getPixel(bgImgS,i,j);
            }
        }

        bgImgS = RF_Engine::instance->getGfx2DSrf("world_bg2");
        for(int i=0; i<640; i++)
        {
            for(int j=0; j<480; j++)
            {
                bgImg2[i][j] = RF_Primitive::getPixel(bgImgS,i,j);
            }
        }

    return;
}

void mainProcess::Update(){
    switch(stateMachine)
    {
        case 1: //MenuOpciones
            if(!RF_Engine::instance->exists("Raton"))
            {
                RF_Engine::instance->newTask(new Raton(),id);
            }

            if("MainMenu" != RF_Engine::instance->taskManager[scene]->type)
            {
                RF_Engine::instance->sendSignal(scene, S_KILL_TREE);
                RF_Engine::instance->time->setFixedCTime();

                scene = RF_Engine::instance->newTask(new MainMenu(),id);
            }
            break;
        case 2: //Game
            if("Game" != RF_Engine::instance->taskManager[scene]->type)
            {
                if(RF_Engine::instance->exists("Raton"))
                {
                    RF_Engine::instance->sendSignal("Raton", S_KILL_TREE);
                    RF_Engine::instance->newTask(new Ingame_Mouse(),-1);
                }

                RF_Engine::instance->sendSignal(scene, S_KILL_TREE);

                RF_Engine::instance->time->setFixedCTime();
                scene = RF_Engine::instance->newTask(new Game(),id);

                RF_SoundManager::playSong(RF_Engine::instance->getAudioClip("GlobalGameJam_Aki"),-1);
            }
            else
            {
                deltacount += RF_Engine::instance->time->deltaTime;
                if(deltacount > 0.025f)
                {
                    Fantasy();
                    step++;
                    deltacount = 0;
                }
            }
            break;
        case 3: //EndScene
            if("EndScene" != RF_Engine::instance->taskManager[scene]->type)
            {
                if(RF_Engine::instance->exists("Raton"))
                {
                    RF_Engine::instance->sendSignal("Raton", S_KILL_TREE);
                }

                RF_Engine::instance->deleteText(-1);
                RF_Engine::instance->sendSignal(scene, S_KILL_TREE);
                scene = RF_Engine::instance->newTask(new EndScene(),id);
            }
            break;
    }
    return;
}

void mainProcess::Fantasy()
{
    if(RF_Background::instance == NULL)
    {
        RF_Engine::instance->newTask(new RF_Background(),-1);
    }

    metang = step*0.02355;
    RF_Background::instance->clearSurface(0x000000);

    b1.x=300+cos(metang*2.5)*150; b1.y=250+sin(metang*2)*150;   b1.z=15;//15
    b2.x=300+sin(metang*1.8)*150; b2.y=250+cos(metang*2.0)*150; b2.z=30;//20
    b3.x=300+sin(metang+100)*150; b3.y=250+cos(metang+50)*150;  b3.z=25;//25
    b4.x=300+sin(metang+2.5)*150; b4.y=250+cos(metang+50)*150;  b4.z=15;//25

    for(mi = 0; mi < 640; mi+=10)
    {
        for(mj = 0; mj < 480; mj+=10)
        {
            result = (b1.z/(pow(sqrt(pow(b1.x-mi,2)+pow(b1.y-mj,2)),goo)) + b2.z/(pow(sqrt(pow(b2.x-mi,2)+pow(b2.y-mj,2)),goo)) + b3.z/(pow(sqrt(pow(b3.x-mi,2)+pow(b3.y-mj,2)),goo)) + b4.z/(pow(sqrt(pow(b4.x-mi,2)+pow(b4.y-mj,2)),goo)));
            if(result>radio)
            {
                for(mii = 0; mii < 10; mii++)
                {
                    for(mjj = 0; mjj < 10; mjj++)
                    {
                        RF_Background::instance->putPixel(mi+mii,mj+mjj,bgImg2[mi+mii][mj+mjj]);
                    }
                }
            }
            else
            {
                for(mii = 0; mii < 10; mii++)
                {
                    for(mjj = 0; mjj < 10; mjj++)
                    {
                        RF_Background::instance->putPixel(mi+mii,mj+mjj,bgImg[mi+mii][mj+mjj]);
                    }
                }
            }
        }
    }
}
