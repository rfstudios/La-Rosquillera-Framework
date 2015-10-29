/*
  LA ROSQUILLERA FRAMEWORK
  Copyright (C) 2015 Yawin <tuzmakel@gmail.com>

  This is an example of videogame. You can use as the fuck you want.
*/

#include "mainprocess.h"
#include "execontrol.h"
#include "prota.h"
#include "enemyspawner.h"

mainProcess::~mainProcess(){}

void mainProcess::Start()
{
    engine->newTask(new exeControl(),id);
    prota=engine->newTask(new Prota(Vector2<float>(640,700)),id);
    engine->newTask(new EnemySpawner(),id);

    return;
}
void mainProcess::Update()
{
    if(!engine->taskManager[prota])
    {
        engine->sendSignal("enemyspawner",S_KILL_TREE);
        engine->manageSignals();

        prota=engine->newTask(new Prota(Vector2<float>(640,700)),id);
        engine->newTask(new EnemySpawner(),id);
    }
    return;
}
