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

#include "rf_window.h"

RF_Window::RF_Window(string i_title, int i_windowMode, int i_posX, int i_posY, int i_width, int i_height, int i_rendererMode)
{
    _title=i_title;
    _windowMode=i_windowMode;
    _posX=i_posX;
    _posY=i_posY;
    _width=i_width;
    _height=i_height;
    _rendererMode=i_rendererMode;
    _index=0;

    window = SDL_CreateWindow(_title.c_str(), _posX, _posY, _width, _height, _windowMode);
    renderer = SDL_CreateRenderer(window,_index,_rendererMode);
}

RF_Window::~RF_Window()
{
    Dispose();
}

void RF_Window::render(vector<RF_Process*>& tM)
{
    SDL_RenderClear(renderer);
    for(int i=0;i<tM.size();i++)
    {
        if(tM[i])
        {
            SDL_Rect r;
            SDL_QueryTexture(tM[i]->graph,NULL,NULL,&r.w,&r.h);

            r.x=tM[i]->transform.position.x; r.y=tM[i]->transform.position.y;

            SDL_RenderCopy(renderer,tM[i]->graph,NULL,&r);
        }
    }
    SDL_RenderPresent(renderer);
}

void RF_Window::Dispose()
{
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
}
