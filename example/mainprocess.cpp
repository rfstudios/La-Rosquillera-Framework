/*
  LA ROSQUILLERA FRAMEWORK
  Copyright (C) 2015 Yawin <tuzmakel@gmail.com>

  This is an example of videogame. You can use as the fuck you want.
*/

#include "mainprocess.h"
#include "execontrol.h"
#include "splashscreen.h"
#include "scene1.h"
#include "scene2.h"
#include "rf_declares.h"
#include <SDL2/SDL_ttf.h>

mainProcess::~mainProcess(){}

void mainProcess::Start()
{
    engine->newTask(new exeControl(),id);

    int bgr = engine->newTask(new background(),id);

    bg = dynamic_cast<background*>(engine->taskManager[bgr]);
    bg->prepareSurface();

    scene = engine->newTask(new SplashScreen(),id);
    return;
}
void mainProcess::Update()
{
    switch(stateMachine)
    {
        case 1: //Scene1
            if("Scene1" != engine->taskManager[scene]->type)
            {
                engine->sendSignal(scene, S_KILL_TREE);
                engine->playSong("resources/st7.wav");
                engine->time->setFixedCTime();

                scene = engine->newTask(new Scene1(),id);
            }
            break;
        case 2: //Scene2
            if("Scene2" != engine->taskManager[scene]->type)
            {
                engine->sendSignal(scene, S_KILL_TREE);

                engine->time->setFixedCTime();
                scene = engine->newTask(new Scene2(),id);
            }
            break;
    }
    return;
}
