/*
  LA ROSQUILLERA FRAMEWORK
  Copyright (C) 2015 Yawin <tuzmakel@gmail.com>

  This is an example of videogame. You can use as the fuck you want.
*/

#include "enemyspawner.h"
#include "enemigo.h"

EnemySpawner::~EnemySpawner(){}

void EnemySpawner::Update()
{
    if(rand()%10000<50)
    {
        engine->newTask(new Enemigo(),id);
    }
}
