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
    graph=engine->loadPNG("resources/nave1.png");
    return;
}
void Prota::Update()
{
    if(engine->key[_a] && transform.position.x>7) transform.position.x-=300*engine->time->deltaTime;
    else if(engine->key[_d] && transform.position.x<1250) transform.position.x+=300*engine->time->deltaTime;

    if(engine->key[_space]){Disparo();}
    else{disparado=0;}

    if(engine->collision("enemigo",this))
    {
        signal=S_KILL;
    }

    return;
}

void Prota::Disparo()
{
    if(disparado<0)
    {
        engine->newTask(new Laser(Vector2<float>(transform.position.x+10,transform.position.y-10)),id);
        disparado=50;
    }

    disparado-=100*engine->time->deltaTime;
}
