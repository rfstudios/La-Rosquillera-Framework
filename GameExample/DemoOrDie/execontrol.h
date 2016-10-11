/*
  LA ROSQUILLERA FRAMEWORK
  Copyright (C) 2015 Yawin <tuzmakel@gmail.com>

  This is an example of videogame. You can use as the fuck you want.
*/

#ifndef EXECONTROL_H
#define EXECONTROL_H

#include "rf_process.h"

class exeControl : public RF_Process
{
    public:
        exeControl():RF_Process("exeProcess"){}
        virtual ~exeControl();

        virtual void Update();
    protected:
    private:
};

#endif // EXECONTROL_H
