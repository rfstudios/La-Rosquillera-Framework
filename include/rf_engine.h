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

#ifndef RF_ENGINE_H
#define RF_ENGINE_H

#include "rf_window.h"
#include "rf_process.h"
#include "rf_declares.h"
#include "rf_time.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <vector>
#include <iostream>
using namespace std;


class RF_Engine
{
    public:
        RF_Engine(bool debug=false);
        virtual ~RF_Engine();
        void run();

        void newWindow(string i_title, int i_windowMode, int i_posX, int i_posY, int i_width, int i_height, int i_rendererMode);
        void destroyWindow();
        RF_Window* ventana;

        /**Ciclo de ejecución**/
            void input();
            void update();
            void render();
        /*********************/

        /**Control de ejecución*******/
            bool isRunning();
            void isRunning(bool m_r);
            bool m_run=true;
        /*****************************/

        /**Task Manager**********************/
            vector<RF_Process*> taskManager;
            int newTask(RF_Process *task,int father=-1);
            void manageSignals();
            void sendSignal(int task, int signal);
            void sendSignal(string type, int signal);
            bool exists(string type);
        /************************************/

        SDL_Event event;    //Evento para controlar teclado
        bool key[_FOO_KEY]; //Array de teclas pulsadas
        RF_Time *time;

        /**Control de debug*******/
            bool isDebug;
            void Debug(string t);
            void Debug(int t);
            void Debug(float t);
        /************************/

        /**Utilities*************/
            SDL_Texture* loadPNG(string file);
            RF_Process* collision(string target, RF_Process* sender);
            RF_Process* collision(int target, RF_Process* sender);
        /************************/
};

#endif // RF_ENGINE_H
