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

#ifndef RF_WINDOW_H
#define RF_WINDOW_H

class RF_Process;
#include "rf_process.h"
#include <SDL2/SDL.h>
#include <string>
#include <vector>
using namespace std;

class RF_Window
{
    public:
        RF_Window(string i_title, int i_windowMode, int i_posX, int i_posY, int i_width, int i_height, int i_rendererMode);
        void render(vector<RF_Process*>& tM);
        void Dispose();
        virtual ~RF_Window();

        SDL_Window*     window;
        SDL_Renderer*   renderer;

    private:
        string          _title;
        int             _windowMode;
        int             _posX;
        int             _posY;
        int             _width;
        int             _height;
        int             _rendererMode;
        int             _index;
};

#endif // RF_WINDOW_H
