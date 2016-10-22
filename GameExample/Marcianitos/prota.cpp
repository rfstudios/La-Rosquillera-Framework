/*
  LA ROSQUILLERA FRAMEWORK
  Copyright (C) 2015 Yawin <tuzmakel@gmail.com>

  This is an example of videogame. You can use as the fuck you want.
*/

#include "prota.h"
#include "laser.h"

Prota::~Prota(){}

void Prota::Start()
{
    graph=RF_Engine::instance->getGfx2D("nave1");
    return;
}
void Prota::Update()
{
    if(RF_Engine::instance->key[_a] && transform.position.x>7) transform.position.x-=300*RF_Engine::instance->time->deltaTime;
    else if(RF_Engine::instance->key[_d] && transform.position.x<1250) transform.position.x+=300*RF_Engine::instance->time->deltaTime;

    if(RF_Engine::instance->key[_space]){Disparo();}
    else{disparado=0;}

    if(RF_Engine::instance->collision("enemigo",this))
    {
        signal=S_KILL;
    }

    return;
}

void Prota::Disparo()
{
    if(disparado<0)
    {
        RF_Engine::instance->newTask(new Laser(Vector2<float>(transform.position.x+10,transform.position.y-10)),id);
        disparado=50;
    }

    disparado-=100*RF_Engine::instance->time->deltaTime;
}
