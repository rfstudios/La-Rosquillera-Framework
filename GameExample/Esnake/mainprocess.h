/*
  LA ROSQUILLERA FRAMEWORK
  Copyright (C) 2015 Yawin <tuzmakel@gmail.com>

  This is an example of videogame. You can use as the fuck you want.
*/

#ifndef MAINPROCESS_H
#define MAINPROCESS_H

#include "rf_process.h"
#include "rf_background.h"

class mainProcess : public RF_Process
{
    public:
        mainProcess():RF_Process("mainProcess"){}
        virtual ~mainProcess();

        virtual void Start();
        virtual void Update();

        RF_Background* bg;

        int& state(){return stateMachine;}

    private:
        int stateMachine = 0;
        int scene;

        void breik(RF_Process* escena){}
};

#endif // MAINPROCESS_H
