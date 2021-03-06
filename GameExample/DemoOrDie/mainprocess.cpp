/*
  LA ROSQUILLERA FRAMEWORK
  Copyright (C) 2015 Yawin <tuzmakel@gmail.com>

  This is an example of a demo. You can use as the fuck you want.
*/

#include "mainprocess.h"
#include "execontrol.h"
#include "splashscreen.h"
#include "scene1.h"
#include "scene2.h"
#include "scene3.h"
#include "scene4.h"
#include "scene5.h"
#include "scene6.h"
#include "rf_declares.h"
#include "rf_primitive.h"
#include "rf_soundmanager.h";
#include <SDL2/SDL_ttf.h>

mainProcess::~mainProcess(){}

void mainProcess::Start()
{
    RF_Engine::instance->newTask(new exeControl(),id);

    RF_Engine::instance->loadAsset("resources/gfx");
    RF_Engine::instance->loadAsset("resources/misc");

    //breik(new Scene1());

    scene = RF_Engine::instance->newTask(new SplashScreen(),id);
    return;
}

void mainProcess::Update()
{
    switch(stateMachine)
    {
        case 1: //Scene1
            if("Scene1" != RF_Engine::instance->taskManager[scene]->type)
            {
                RF_Engine::instance->sendSignal(scene, S_KILL_TREE);
                RF_SoundManager::playSong("st7",0);
                RF_Engine::instance->time->setFixedCTime();

                scene = RF_Engine::instance->newTask(new Scene1(),id);
            }
            break;
        case 2: //Scene2
            if("Scene2" != RF_Engine::instance->taskManager[scene]->type)
            {
                RF_Engine::instance->sendSignal(scene, S_KILL_TREE);

                RF_Engine::instance->time->setFixedCTime();
                scene = RF_Engine::instance->newTask(new Scene2(),id);
            }
            break;
        case 3: //Scene3
            if("Scene3" != RF_Engine::instance->taskManager[scene]->type)
            {
                RF_Engine::instance->sendSignal(scene, S_KILL_TREE);

                RF_Engine::instance->time->setFixedCTime();
                scene = RF_Engine::instance->newTask(new Scene3(),id);
            }
            break;
        case 4: //Scene4
            if("Scene4" != RF_Engine::instance->taskManager[scene]->type)
            {
                RF_Engine::instance->sendSignal(scene, S_KILL_TREE);

                RF_Engine::instance->time->setFixedCTime();
                scene = RF_Engine::instance->newTask(new Scene4(),id);
            }
            break;
        case 5: //Scene5
            if("Scene5" != RF_Engine::instance->taskManager[scene]->type)
            {
                RF_Engine::instance->sendSignal(scene, S_KILL_TREE);

                RF_Engine::instance->time->setFixedCTime();
                scene = RF_Engine::instance->newTask(new Scene5(),id);
            }
            break;
        case 6: //Scene6
            if("Scene6" != RF_Engine::instance->taskManager[scene]->type)
            {
                RF_Engine::instance->sendSignal(scene, S_KILL_TREE);

                RF_Engine::instance->time->setFixedCTime();
                scene = RF_Engine::instance->newTask(new Scene6(),id);
            }
            break;
        case 7: //Fin
            RF_Engine::instance->sendSignal(scene, S_KILL_TREE);
            RF_Engine::instance->isRunning(false);

            stateMachine = -1;
            break;
    }
    return;
}

void mainProcess::breik(RF_Process* escena){
    scene = RF_Engine::instance->newTask(escena,id);
    stateMachine = -1;
}
