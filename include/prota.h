/*
  LA ROSQUILLERA FRAMEWORK
  Copyright (C) 2015 Yawin <tuzmakel@gmail.com>

  This is an example of videogame. You can use as the fuck you want.
*/

#ifndef PROTA_H
#define PROTA_H

#include "rf_process.h"

class Prota : public RF_Process
{
    public:
        Prota(Vector2<float> pos):RF_Process("prota"){transform.position=pos;}
        virtual ~Prota();

        virtual void Start();
        virtual void Update();

    private:
        float disparado=0.0f;
        void Disparo();
};

#endif // PROTA_H
