/*
  LA ROSQUILLERA FRAMEWORK
  Copyright (C) 2015 Yawin <tuzmakel@gmail.com>

  This is an example of videogame. You can use as the fuck you want.
*/

#include "execontrol.h"

exeControl::~exeControl(){}

void exeControl::Update()
{
    //Escuchamos si se pulsa la tecla (esc) o el boton de cierre de ventana
        if(RF_Engine::instance->key[_esc] || RF_Engine::instance->key[_close_window])
        {
            //En caso afirmativo, apagamos el motor
                RF_Engine::instance->isRunning(false);
        }
}
