/*
  LA ROSQUILLERA FRAMEWORK
  Copyright (C) 2015 Yawin <tuzmakel@gmail.com>

  This is an example of videogame. You can use as the fuck you want.
*/

#include "mainprocess.h"
#include "execontrol.h"
#include "prota.h"
#include "enemigo.h"

mainProcess::~mainProcess(){}

void mainProcess::Start()
{
    engine->newTask(new exeControl(),id);
    prota=engine->newTask(new Prota(Vector2<float>(640,700)),id);

    YGF *newYGF = new YGF();
    newYGF->names.push_back("Pito");
    newYGF->names.push_back("Caca");
    newYGF->names.push_back("Culo");
    newYGF->names.push_back("Pedo");
    newYGF->names.push_back("Pis ");

    engine->ygf.push_back(newYGF);
    engine->playSong("resources/st7.wav");
    return;
}
void mainProcess::Update()
{
    if(!engine->taskManager[prota])
    {
        engine->sendSignal("enemigo",S_KILL);
        engine->manageSignals();

        prota=engine->newTask(new Prota(Vector2<float>(640,700)),id);
    }
    else
    {
        int nRandom=rand()%10000;
        if(nRandom<50)
        {
            engine->newTask(new Enemigo(),id);
        }
    }
    return;
}