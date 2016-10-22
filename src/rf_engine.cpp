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
        Debug("Version de debug");
    }

    math = new RF_Math();

    SDL_ShowCursor(0);
}
RF_Engine::~RF_Engine(){
    for(unsigned int i=0;i<taskManager.size();i++)
    {
        delete(taskManager[i]);
    }
    taskManager.clear();

    delete(ventana);

    //if(NULL != music) Mix_FreeMusic(music); Habrá que parar el SoundManager
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

    if(isDebug)
    {
        write("Version de debug", {255,255,255}, Vector2<int>(ventana->width()-164,ventana->height()-30));
    }
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

    for(unsigned int i=0;i<taskManager.size();i++)
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
    for(unsigned int i = 0; i < taskManager.size(); i++)
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
    for(unsigned int i=0;i<taskManager.size();i++)
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

                    for(unsigned int ii=0;ii<taskManager.size();ii++)
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

                    for(unsigned int ii=0;ii<taskManager.size();ii++)
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
                    for(unsigned int ii=0;ii<taskManager.size();ii++)
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
void RF_Engine::sendSignal(unsigned int task, int signal){
    if(task<taskManager.size() && taskManager[task])
    {
        taskManager[task]->signal=signal;
    }
}
void RF_Engine::sendSignal(string type, int signal){
    for(unsigned int i=0;i<taskManager.size();i++)
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
    for(unsigned int i=0;i<taskManager.size();i++)
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

/**Assets********************************************************/
void RF_Engine::loadAsset(string path){
    RF_Asset_List* nA = new RF_Asset_List(path);
    assetManager.push_back(nA);
}

SDL_Texture* RF_Engine::getGfx2D(string id){
    return SDL_CreateTextureFromSurface(ventana->renderer, getGfx2DSrf(id));
}
SDL_Surface* RF_Engine::getGfx2DSrf(string id){
    RF_Engine::instance->Debug(id);

    int pos = -1; unsigned int i;
    for(i = 0; i < assetManager.size() && pos == -1; i++)
    {
        pos = _search_in_assetManager(i,id);
    }

    SDL_Surface* ret = NULL;
    if(pos != -1)
    {
        i--;
        ret = dynamic_cast<RF_Gfx2D*>(assetManager[i]->assets[pos])->texture;
    }

    return ret;
}
Mix_Music* RF_Engine::getAudioClip(string id){
    RF_Engine::instance->Debug(id);

    int pos = -1; unsigned int i;
    for(i = 0; i < assetManager.size() && pos == -1; i++)
    {
        pos = _search_in_assetManager(i,id);
    }

    Mix_Music* ret = NULL;
    if(pos != -1)
    {
        i--;
        ret = dynamic_cast<RF_AudioClip*>(assetManager[i]->assets[pos])->clip;
    }

    return ret;
}
TTF_Font* RF_Engine::getFont(string id){
    RF_Engine::instance->Debug(id);

    int pos = -1; unsigned int i;
    for(i = 0; i < assetManager.size() && pos == -1; i++)
    {
        pos = _search_in_assetManager(i,id);
    }

    TTF_Font* ret = NULL;
    if(pos != -1)
    {
        i--;
        ret = dynamic_cast<RF_Font*>(assetManager[i]->assets[pos])->font;
    }

    return ret;
}

int RF_Engine::_search_in_assetManager(int i, string id){
    RF_Asset_List* sL = assetManager[i];
    int pos = -1;

    for(int j = sL->assets.size()-1; j >= 0; j--)
    {
        if(sL->assets[j]->id == id)
        {
            pos = j;
            break;
        }
    }

    sL = NULL;
    return pos;
}
int RF_Engine::assetCount(string id){
    int pos = -1; unsigned int i;
    for(i = 0; i < assetManager.size() && pos == -1; i++)
    {
        if(assetManager[i]->id == id)
        {
            pos = i;
        }
    }

    return assetCount(pos);
}
int RF_Engine::assetCount(int id){
    return assetManager[id]->assets.size();
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
    for(unsigned int i=0;i<taskManager.size();i++)
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
int RF_Engine::write(string txt, SDL_Color color, Vector2<float> pos){
    Vector2<int> posInt; posInt.x = (int)pos.x; posInt.y = (int)pos.y;
    return write(txt, color, posInt);
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
    for(unsigned int i = 0; i < textSources.size(); i++)
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
        for(unsigned int i=0;i<textSources.size();i++)
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

Vector2<int> RF_Engine::rotozoom(Vector2<int> pos, Transform2D<int> t, Vector2<int> lim, Vector2<bool> mirror){
    if(t.scale.x == 0) t.scale.x = 1;
    if(t.scale.y == 0) t.scale.y = 1;

    retorno.x=-t.position.x + pos.x * t.scale.x;
    retorno.y=-t.position.y + pos.y * t.scale.y;

    retorno.x = retorno.x * math->preCos(t.rotation*1000) - retorno.y * math->preSin(t.rotation*1000);
    retorno.y = retorno.y * math->preSin(t.rotation*1000) + retorno.y * math->preCos(t.rotation*1000);

    if(retorno.x < 0 || retorno.x > lim.x - 1)
    {
        if(true == mirror.x)
        {
            retorno.x = retorno.x % lim.x;
            if(retorno.x < 0){retorno.x = lim.x + retorno.x;}
        }
        else
        {
            if(retorno.x < 0){retorno.x = 0;}
            if(retorno.x > lim.x - 1){retorno.x = lim.x - 1;}
        }
    }
    if(retorno.y < 0 || retorno.y > lim.y - 1)
    {
        if(false == mirror.y)
        {
            if(retorno.y < 0){retorno.y = 0;}
            if(retorno.y > lim.y - 1){retorno.y = lim.y - 1;}
        }
        else
        {
            retorno.y = retorno.y % lim.y;
            if(retorno.y < 0){retorno.y = lim.y + retorno.y;}
        }
    }

    return retorno;
}
