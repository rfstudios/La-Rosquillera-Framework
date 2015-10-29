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

    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
            case SDL_QUIT: //Si pulsamos el botón de cerrar ventana
                key[_close_window]=true;
                break;

            default:
                break;
        }
    }
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

                    delete(taskManager[i]);
                    taskManager[i]=NULL;
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
bool RF_Engine::exists(string type){
    for(int i=0;i<taskManager.size();i++)
    {
        if(taskManager[i])
        {
            if(taskManager[i]->type==type)
            {
                return true;
            }
        }
    }

    return false;
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

    return NULL;
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

