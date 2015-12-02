/*
  LA ROSQUILLERA FRAMEWORK
  Copyright (C) 2015 Yawin <tuzmakel@gmail.com>

  This is an example of videogame. You can use as the fuck you want.
*/

#ifndef LASER_H
#define LASER_H

#include "rf_process.h"

class Laser : public RF_Process
{
    public:
        Laser(Vector2<float> pos):RF_Process("laser"){transform.position=pos;}
        virtual ~Laser();

        virtual void Start();
        virtual void Update();
};

#endif // LASER_H
