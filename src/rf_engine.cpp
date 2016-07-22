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
#include <SDL2/SDL_image.h>
using namespace std;

RF_Engine* RF_Engine::instance = NULL;

RF_Engine::RF_Engine(bool debug){
    RF_Engine::instance = this;

    isDebug=debug;
    SDL_Init(SDL_INIT_EVERYTHING);
    IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG);
    Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096);
    TTF_Init();
    font = TTF_OpenFont("resources/Coving01.ttf", 20);

    time=new RF_Time();
    ventana = new RF_Window("",SDL_WINDOW_HIDDEN,0,0,1,1,SDL_RENDERER_ACCELERATED);

    if(isDebug)
    {
        write("Version de debug", {255,255,255}, Vector2<int>(476,450));
        Debug("Version de debug");
    }

    SDL_ShowCursor(0);
}
RF_Engine::~RF_Engine(){
    for(int i=0;i<taskManager.size();i++)
    {
        delete(taskManager[i]);
    }
    taskManager.clear();

    delete(ventana);

    if(NULL != music) Mix_FreeMusic(music);
    Mix_Quit();
    TTF_Quit();
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
        if(NULL != taskManager[i])
        {
            if(taskManager[i]->signal==S_AWAKE)
            {
                taskManager[i]->Update();
            }
        }
    }
}
void RF_Engine::render(){
    ventana->render(taskManager, textSources);
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
    int pos = getPlace();
    if(0 > pos)
    {
        taskManager.push_back(task);
        pos = taskManager.size()-1;
    }
    else
    {
        taskManager[pos] = task;
    }

    taskManager[pos]->father=father;
    taskManager[pos]->id=pos;
    taskManager[pos]->Start();
    return pos;
}
int RF_Engine::getPlace(){
    int _pos = -1;
    for(int i = 0; i < taskManager.size(); i++)
    {
        if(NULL == taskManager[i])
        {
            _pos = i;
            break;
        }
    }

    return _pos;
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
                    taskManager[i] = NULL;
                    break;
                case S_SLEEP_TREE:
                    taskManager[i]->signal = S_SLEEP;

                    for(int ii=0;ii<taskManager.size();ii++)
                    {
                        if(taskManager[ii])
                        {
                            if(taskManager[ii]->father==i)
                            {
                                taskManager[ii]->signal = S_SLEEP;
                            }
                        }
                    }
                    break;
                case S_AWAKE_TREE:
                    taskManager[i]->signal = S_AWAKE;

                    for(int ii=0;ii<taskManager.size();ii++)
                    {
                        if(taskManager[ii])
                        {
                            if(taskManager[ii]->father==i)
                            {
                                taskManager[ii]->signal = S_AWAKE;
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
                                taskManager[ii] = NULL;
                            }
                        }
                    }

                    delete(taskManager[i]);
                    taskManager[i] = NULL;
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
SDL_Surface* RF_Engine::loadPNG_Surface(string file){
    return IMG_Load(file.c_str());
}
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
void RF_Engine::playSong(string file){
        if(NULL != music)
        {
            Mix_FreeMusic(music);
        }

        music = Mix_LoadMUS(file.c_str());
        Mix_PlayMusic(music, 0);
}
int RF_Engine::write(string txt, SDL_Color color, Vector2<float> pos){
    Vector2<int> posInt; posInt.x = (int)pos.x; posInt.y = (int)pos.y;
    write(txt, color, posInt);
}
int RF_Engine::write(string txt, SDL_Color color, Vector2<int> pos){
    if(NULL != font)
    {
        SDL_Surface* textSurface = TTF_RenderText_Solid(font, txt.c_str(), color);
        YW_Text* tmpTxt = new YW_Text();
        tmpTxt->textSurface = textSurface;
        tmpTxt->position = pos;

        int pos = _writeGetPlace();
        if(-1 == pos)
        {
            textSources.push_back(tmpTxt);
            pos = textSources.size()-1;
        }
        else
        {
            textSources[pos] = tmpTxt;

        }
        return pos;
    }
    else
    {
        Debug("No hay fuente asignada");
        return -1;
    }
}
 int RF_Engine::_writeGetPlace(){
    int _pos = -1;
    for(int i = 0; i < textSources.size(); i++)
    {
        if(NULL == textSources[i])
        {
            _pos = i;
            break;
        }
    }

    return _pos;
}
void RF_Engine::deleteText(int txtID){
    if(-1 >= txtID)
    {
        for(int i=0;i<textSources.size();i++)
        {
            delete(textSources[i]);
            textSources[i] = NULL;
        }
        textSources.clear();
    }
    else
    {
        delete(textSources[txtID]);
        textSources[txtID] = NULL;
    }
}

int RF_Engine::loadYgf(string filename){
    /*
        1 - Abrimos el fichero comprimido
        2 - Descomprimimos uno a uno cada fichero
        3 - Hacemos el while
    */

    YGF *newYGF = new YGF(); //Creamos una nueva estructura YGF
    while(true)//Para cada fichero dentro del comprimido
    {
        //Extraemos el fichero

        //Creamos la SDL_Texture
        //SDL_Texture *g = new SDL_Texture();
        /*SDL_RWops *rw;
        rw=SDL_RWFromMem();
        SDL_Texture *t = SDL_CreateTextureFromSurface(ventana->renderer,IMG_LoadPNG_RW(rw));
        newYGF->graph.push_back(t);
        SDL_FreeRW(rw);*/
    }
    ygf.push_back(newYGF);

}
