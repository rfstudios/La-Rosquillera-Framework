/*
  LA ROSQUILLERA FRAMEWORK
  Copyright (C) 2015 Yawin <tuzmakel@gmail.com>

  This is an example of videogame. You can use as the fuck you want.
*/

#ifndef ENEMYSPAWNER_H
#define ENEMYSPAWNER_H

#include "rf_process.h"

class EnemySpawner : public RF_Process
{
    public:
        EnemySpawner():RF_Process("enemyspawner"){}
        virtual ~EnemySpawner();

        virtual void Update();
};

#endif // ENEMYSPAWNER_H
