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

#include "rf_engine.h"
#include <string>
using namespace std;

RF_Engine::RF_Engine(bool debug){
    isDebug=debug;
    SDL_Init(SDL_INIT_EVERYTHING);
    IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG);

    time=new RF_Time();
}
RF_Engine::~RF_Engine(){
    for(int i=0;i<taskManager.size();i++)
    {
        delete(taskManager[i]);
    }
    taskManager.clear();

    delete(ventana);
    IMG_Quit();
    SDL_Quit();
}

void RF_Engine::newWindow(string title, int windowMode, int posX, int posY, int width, int height, int rendererMode){
    if(ventana)
    {
        destroyWindow();
    }
    ventana = new RF_Window(title,windowMode,posX,posY,width,height,rendererMode);
}
void RF_Engine::destroyWindow(){
    delete(ventana);
}

void RF_Engine::run(){
    input();
    update();
    render();
}

/**Ciclo de ejecución*********************************************/
void RF_Engine::input(){
    SDL_PumpEvents();
    for(int i=0;i<_FOO_KEY;i++)
    {
        key[i]=false;
    }

    const Uint8 *keys=SDL_GetKeyboardState(NULL);
    for(Uint8 i=SDL_SCANCODE_A;i<=SDL_SCANCODE_SPACE;i++)
    {
        key[i-4]=keys[i];
    }

    /*while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
            case SDL_QUIT: //Si pulsamos el botón de cerrar ventana
                key[_close_window]=true;
                break;

            case SDL_KEYDOWN:
                switch (event.key.keysym.sym)
                {
                    case SDLK_ESCAPE:
                        key[_esc]=true;
                        break;
                    case SDLK_1:
                        key[_1]=true;
                        break;
                    case SDLK_2:
                        key[_2]=true;
                        break;
                    case SDLK_3:
                        key[_3]=true;
                        break;
                    case SDLK_4:
                        key[_4]=true;
                        break;
                    case SDLK_5:
                        key[_5]=true;
                        break;
                    case SDLK_6:
                        key[_6]=true;
                        break;
                    case SDLK_7:
                        key[_7]=true;
                        break;
                    case SDLK_8:
                        key[_8]=true;
                        break;
                    case SDLK_9:
                        key[_9]=true;
                        break;
                    case SDLK_0:
                        key[_0]=true;
                        break;
                    case SDLK_MINUS:
                        key[_minus]=true;
                        break;
                    case SDLK_PLUS:
                        key[_plus]=true;
                        break;
                    case SDLK_BACKSPACE:
                        key[_backspace]=true;
                        break;
                    case SDLK_TAB:
                        key[_tab]=true;
                        break;
                    case SDLK_q:
                        key[_q]=true;
                        break;
                    case SDLK_w:
                        key[_w]=true;
                        break;
                    case SDLK_e:
                        key[_e]=true;
                        break;
                    case SDLK_r:
                        key[_r]=true;
                        break;
                    case SDLK_t:
                        key[_t]=true;
                        break;
                    case SDLK_y:
                        key[_y]=true;
                        break;
                    case SDLK_u:
                        key[_u]=true;
                        break;
                    case SDLK_i:
                        key[_i]=true;
                        break;
                    case SDLK_o:
                        key[_o]=true;
                        break;
                    case SDLK_p:
                        key[_p]=true;
                        break;
                    case SDLK_a:
                        key[_a]=true;
                        break;
                    case SDLK_s:
                        key[_s]=true;
                        break;
                    case SDLK_d:
                        key[_d]=true;
                        break;
                    case SDLK_f:
                        key[_f]=true;
                        break;
                    case SDLK_g:
                        key[_g]=true;
                        break;
                    case SDLK_h:
                        key[_h]=true;
                        break;
                    case SDLK_j:
                        key[_j]=true;
                        break;
                    case SDLK_k:
                        key[_k]=true;
                        break;
                    case SDLK_l:
                        key[_l]=true;
                        break;
                    case SDLK_z:
                        key[_z]=true;
                        break;
                    case SDLK_x:
                        key[_x]=true;
                        break;
                    case SDLK_c:
                        key[_c]=true;
                        break;
                    case SDLK_v:
                        key[_v]=true;
                        break;
                    case SDLK_b:
                        key[_b]=true;
                        break;
                    case SDLK_n:
                        key[_n]=true;
                        break;
                    case SDLK_m:
                        key[_m]=true;
                        break;
                    case SDLK_F1:
                        key[_f1]=true;
                        break;
                    case SDLK_F2:
                        key[_f2]=true;
                        break;
                    case SDLK_F3:
                        key[_f3]=true;
                        break;
                    case SDLK_F4:
                        key[_f4]=true;
                        break;
                    case SDLK_F5:
                        key[_f5]=true;
                        break;
                    case SDLK_F6:
                        key[_f6]=true;
                        break;
                    case SDLK_F7:
                        key[_f7]=true;
                        break;
                    case SDLK_F8:
                        key[_f8]=true;
                        break;
                    case SDLK_F9:
                        key[_f9]=true;
                        break;
                    case SDLK_F10:
                        key[_f10]=true;
                        break;
                    case SDLK_F11:
                        key[_f11]=true;
                        break;
                    case SDLK_F12:
                        key[_f12]=true;
                        break;
                    case SDLK_RETURN:
                        key[_enter]=true;
                        break;
                    case SDLK_RETURN2:
                        key[_c_enter]=true;
                        break;
                    case SDLK_LCTRL:
                        key[_l_control]=true;
                        break;
                    case SDLK_LSHIFT:
                        key[_l_shift]=true;
                        break;
                    case SDLK_COMMA:
                        key[_comma]=true;
                        break;
                    case SDLK_PERIOD:
                        key[_point]=true;
                        break;
                    case SDLK_RSHIFT:
                        key[_r_shift]=true;
                        break;
                    case SDLK_PRINTSCREEN:
                        key[_prn_scr]=true;
                        break;
                    case SDLK_LALT:
                        key[_l_alt]=true;
                        break;
                    case SDLK_CAPSLOCK:
                        key[_caps_lock]=true;
                        break;
                    case SDLK_NUMLOCKCLEAR:
                        key[_num_lock]=true;
                        break;
                    case SDLK_SCROLLLOCK:
                        key[_scroll_lock]=true;
                        break;
                    case SDLK_HOME:
                        key[_home]=true;
                        break;
                    case SDLK_AC_HOME:
                        key[_c_home]=true;
                        break;
                    case SDLK_UP:
                        key[_up]=true;
                        break;
                    case SDLK_DOWN:
                        key[_down]=true;
                        break;
                    case SDLK_LEFT:
                        key[_left]=true;
                        break;
                    case SDLK_RIGHT:
                        key[_right]=true;
                        break;
                    case SDLK_RCTRL:
                        key[_r_control]=true;
                        break;

                    default:
                        break;
                }
                break;

            default:
                break;
        }
    }*/
}
void RF_Engine::update(){
    manageSignals();
    time->Update();

    for(int i=0;i<taskManager.size();i++)
    {
        if(taskManager[i])
        {
            if(taskManager[i]->signal==S_AWAKE)
            {
                taskManager[i]->Update();
            }
        }
    }
}
void RF_Engine::render(){
    ventana->render(taskManager);
}
/****************************************************************/

/**Control de ejecución******************************************/
bool RF_Engine::isRunning(){
    return m_run;
}
void RF_Engine::isRunning(bool m_r){
    m_run=m_r;
}
/****************************************************************/

/**Task Manager**************************************************/
int RF_Engine::newTask(RF_Process *task, int father){
    taskManager.push_back(task);
    taskManager[taskManager.size()-1]->father=father;
    taskManager[taskManager.size()-1]->id=taskManager.size()-1;
    taskManager[taskManager.size()-1]->setEngine(this);
    taskManager[taskManager.size()-1]->Start();
    return taskManager.size()-1;
}
void RF_Engine::manageSignals(){
    for(int i=0;i<taskManager.size();i++)
    {
        if(taskManager[i])
        {
            switch(taskManager[i]->signal)
            {
                case S_KILL:
                    delete(taskManager[i]);
                    taskManager[i]=NULL;
                    break;
                case S_SLEEP_TREE:
                    taskManager[i]->signal=S_SLEEP;

                    for(int ii=0;ii<taskManager.size();ii++)
                    {
                        if(taskManager[ii])
                        {
                            if(taskManager[ii]->father==i)
                            {
                                taskManager[ii]->signal=S_SLEEP;
                            }
                        }
                    }
                    break;
                case S_AWAKE_TREE:
                    taskManager[i]->signal=S_AWAKE;

                    for(int ii=0;ii<taskManager.size();ii++)
                    {
                        if(taskManager[ii])
                        {
                            if(taskManager[ii]->father==i)
                            {
                                taskManager[ii]->signal=S_AWAKE;
                            }
                        }
                    }
                    break;
                case S_KILL_TREE:
                    delete(taskManager[i]);
                    taskManager[i]=NULL;

                    for(int ii=0;ii<taskManager.size();ii++)
                    {
                        if(taskManager[ii])
                        {
                            if(taskManager[ii]->father==i)
                            {
                                delete(taskManager[ii]);
                                taskManager[ii]=NULL;
                            }
                        }
                    }
                    break;
            }
        }
    }
}
void RF_Engine::sendSignal(int task, int signal){
    if(task<taskManager.size() && taskManager[task])
    {
        taskManager[task]->signal=signal;
    }
}
void RF_Engine::sendSignal(string type, int signal){
    for(int i=0;i<taskManager.size();i++)
    {
        if(taskManager[i])
        {
            if(taskManager[i]->type==type)
            {
                taskManager[i]->signal=signal;
            }
        }
    }
}
/****************************************************************/

/**Control de Debug**********************************************/
void RF_Engine::Debug(string t){
    if(isDebug)
        cout<<t<<endl;
}
void RF_Engine::Debug(int t){
    if(isDebug)
        cout<<t<<endl;
}
void RF_Engine::Debug(float t){
    if(isDebug)
        cout<<t<<endl;
}
/****************************************************************/

/**Utilidades****************************************************/
SDL_Texture* RF_Engine::loadPNG(string file){
    return IMG_LoadTexture(ventana->renderer,file.c_str());
}

RF_Process* RF_Engine::collision(string target, RF_Process* sender){
    for(int i=0;i<taskManager.size();i++)
    {
        if(taskManager[i])
        {
            if(taskManager[i]->type==target)
            {
                RF_Process *p=collision(i,sender);
                if(p){return p;}
            }
        }
    }
}
RF_Process* RF_Engine::collision(int target, RF_Process* sender){
    RF_Process *t=taskManager[target];
    Vector2<int> pscal1,pscal2,ppos1,ppos2;

    ppos1.x=(int)sender->transform.position.x; ppos1.y=(int)sender->transform.position.y;
    ppos2.x=(int)t->transform.position.x; ppos2.y=(int)t->transform.position.y;
    SDL_QueryTexture(sender->graph,NULL,NULL,&pscal1.x,&pscal1.y);
    SDL_QueryTexture(t->graph,NULL,NULL,&pscal2.x,&pscal2.y);

    if((ppos1.x+pscal1.x)>ppos2.x && (ppos1.y+pscal1.y)>ppos2.y && (ppos2.x+pscal2.x)>ppos1.x && (ppos2.y+pscal2.y)>ppos1.y)
    {
        return t;
    }

    return NULL;
}
/****************************************************************/

