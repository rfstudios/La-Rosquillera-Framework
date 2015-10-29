/*
  LA ROSQUILLERA FRAMEWORK
  Copyright (C) 2015 Yawin <tuzmakel@gmail.com>

  This is an example of videogame. You can use as the fuck you want.
*/

#include "enemigo.h"
#include "rf_process.h"

Enemigo::~Enemigo(){}

void Enemigo::Start()
{
    transform.position.y=-10;
    transform.position.x=rand()%1200+40;
    graph=engine->loadPNG("resources/nave2.png");

    velocidad.y=rand()%50+25;
    velocidad.x=rand()%100-50;
}

void Enemigo::Update()
{
    transform.position.x+=velocidad.x*engine->time->deltaTime;
    transform.position.y+=velocidad.y*engine->time->deltaTime;

    RF_Process *laser=engine->collision("laser",this);
    if(laser)
    {
        engine->sendSignal(laser->id,S_KILL);
        signal=S_KILL;
    }

    if(transform.position.x<-20 || transform.position.x>1290 || transform.position.y>740) signal=S_KILL;
}
