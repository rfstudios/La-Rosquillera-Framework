/*
  LA ROSQUILLERA FRAMEWORK
  Copyright (C) 2015 Yawin <tuzmakel@gmail.com>

  This is an example of videogame. You can use as the fuck you want.
*/

#ifndef ENEMIGO_H
#define ENEMIGO_H

#include "rf_process.h"

class Enemigo : public RF_Process
{
    public:
        Enemigo():RF_Process("enemigo"){}
        virtual ~Enemigo();

        virtual void Start();
        virtual void Update();

    private:
        Vector2<float> velocidad;
};

#endif // ENEMIGO_H
