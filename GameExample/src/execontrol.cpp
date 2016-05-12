/*
  LA ROSQUILLERA FRAMEWORK
  Copyright (C) 2015 Yawin <tuzmakel@gmail.com>

  This is an example of videogame. You can use as the fuck you want.
*/

#include "execontrol.h"

exeControl::~exeControl(){}

void exeControl::Update()
{
    if(engine->key[_esc] || engine->key[_close_window])
    {
        engine->isRunning(false);
    }
}
