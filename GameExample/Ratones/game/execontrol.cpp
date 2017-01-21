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
