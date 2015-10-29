/*
  LA ROSQUILLERA FRAMEWORK
  Copyright (C) 2015 Yawin <tuzmakel@gmail.com>

  This software is provided 'as-is', without any express or implied
  warranty.  In no event will the authors be held liable for any damages
  arising from the use of this software.

  Permission is granted to anyone to use this software for any purpose,
  including commercial applications, and to alter it and redistribute it
  freely, subject to the following restrictions:

  1. The origin of this software must not be misrepresented; you must not
     claim that you wrote the original software. If you use this software
     in a product, an acknowledgment in the product documentation would be
     appreciated but is not required.
  2. Altered source versions must be plainly marked as such, and must not be
     misrepresented as being the original software.
  3. This notice may not be removed or altered from any source distribution.
*/

#ifndef RF_PROCESS_H
#define RF_PROCESS_H

#include "rf_engine.h"
#include "rf_declares.h"
#include <SDL2/SDL_image.h>
#include <string>
using namespace std;

class RF_Process
{
    public:
        RF_Process(string _type="", int _father=-1);
        virtual ~RF_Process();

        virtual void Start();
        virtual void Update();

        /**Propiedades******/
            int id, father, signal=S_AWAKE;
            string type="";
            SDL_Texture *graph;
            Transform transform;
        /*******************/

        void setEngine(RF_Engine *e);

    protected:
        RF_Engine *engine;
};

#endif // RF_PROCESS_H
