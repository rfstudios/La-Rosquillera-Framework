/*
  LA ROSQUILLERA FRAMEWORK
  Copyright (C) 2015 Yawin <tuzmakel@gmail.com>

  This is an example of videogame. You can use as the fuck you want.
*/

#include "mainprocess.h"
#include "execontrol.h"
#include "prota.h"
#include "enemigo.h"
#include "rf_soundmanager.h"

mainProcess::~mainProcess(){}

void mainProcess::Start()
{
    RF_Engine::instance->newTask(new exeControl(),id);
    RF_Engine::instance->loadAsset("resources");
    RF_SoundManager::playSong("musica");

    prota=RF_Engine::instance->newTask(new Prota(Vector2<float>(640,700)),id);
    return;
}
void mainProcess::Update()
{
    if(!RF_Engine::instance->taskManager[prota])
    {
        RF_Engine::instance->sendSignal("enemigo",S_KILL);
        RF_Engine::instance->manageSignals();

        prota=RF_Engine::instance->newTask(new Prota(Vector2<float>(640,700)),id);
    }
    else
    {
        int nRandom=rand()%10000;
        if(nRandom<50)
        {
            RF_Engine::instance->newTask(new Enemigo(),id);
        }
    }
    return;
}
