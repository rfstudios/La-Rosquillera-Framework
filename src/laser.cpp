/*
  LA ROSQUILLERA FRAMEWORK
  Copyright (C) 2015 Yawin <tuzmakel@gmail.com>

  This is an example of videogame. You can use as the fuck you want.
*/

#include "laser.h"

Laser::~Laser(){}

void Laser::Start()
{
    graph=engine->loadPNG("resources/laser.png");
}

void Laser::Update()
{
    transform.position.y-=400*engine->time->deltaTime;
    if(transform.position.y<10) signal=S_KILL;
}
