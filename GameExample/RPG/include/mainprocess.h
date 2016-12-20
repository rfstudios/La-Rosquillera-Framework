/*
  LA ROSQUILLERA FRAMEWORK
  Copyright (C) 2015 Yawin <tuzmakel@gmail.com>

  This is an example of videogame. You can use as the fuck you want.
*/

#ifndef MAINPROCESS_H
#define MAINPROCESS_H

#include "rf_process.h"
#include <rf_background.h>
#include <rf_declares.h>
#include <rf_primitive.h>
#include <rf_soundmanager.h>
#include <SDL2/SDL_ttf.h>

#include "execontrol.h"

class mainProcess : public RF_Process
{
    public:
        mainProcess():RF_Process("mainProcess"){}
        virtual ~mainProcess(){}

        virtual void Start()
        {
            //Levantamos el proceso que detectará, durante toda la ejecución, si pulsamos
            //la tecla esc;
                RF_Engine::instance->newTask(new exeControl(),id);

            //Levantamos el proceso que controla el fondo
                RF_Engine::instance->newTask(new RF_Background(),id);
            //Inicializamos el fondo
                RF_Background::instance->prepareSurface();

            return;
        }
        virtual void Update(){}

        int& state(){return stateMachine;}

    private:
        int stateMachine = 0;
        int scene;

        void breik(RF_Process* escena){}
};

#endif // MAINPROCESS_H
