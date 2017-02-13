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
#include "rf_primitive.h"
#include "rf_background.h"
#include <string>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mouse.h>
using namespace std;

RF_Engine* RF_Engine::instance = NULL;

RF_Engine::RF_Engine(bool debug){
    RF_Engine::instance = this;

    isDebug=debug;
    SDL_Init(SDL_INIT_EVERYTHING);
    IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG);
    Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 4096);
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

    //Levantamos el proceso que controla el fondo
        newTask(new RF_Background(),-1);

    //Inicializamos el fondo
        RF_Background::instance->prepareSurface();
}
void RF_Engine::destroyWindow(){
    delete(ventana);
}

void RF_Engine::run(){
    wait_to_draw = 0;

    do
    {
        wait_to_draw += RF_Engine::instance->time->deltaTime;
        input();
        update();
    }while(wait_to_draw < 1 / (float)fps);

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

            case SDL_MOUSEMOTION:
                SDL_GetMouseState(&mouse.x,&mouse.y);
                //SDL_GetGlobalMouseState();
                break;

            case SDL_MOUSEBUTTONDOWN:
                mouse.z = 1;
                break;

            case SDL_MOUSEBUTTONUP:
                mouse.z = 0;
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
    for(unsigned int i=0;i<taskManager.size();i++)
    {
        if(NULL != taskManager[i])
        {
            taskManager[i]->Draw();
        }
    }

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
    taskManager[pos]->zLayer = taskManager.size();
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
                                taskManager[ii]->signal = S_KILL_TREE;
                            }
                        }
                    }

                    delete(taskManager[i]);
                    taskManager[i] = NULL;
                    break;
                case S_KILL_CHILD:
                    for(unsigned int ii=0;ii<taskManager.size();ii++)
                    {
                        if(taskManager[ii])
                        {
                            if(taskManager[ii]->father==i)
                            {
                                taskManager[ii]->signal = S_KILL_TREE;
                            }
                        }
                    }

                    taskManager[i]->signal = S_AWAKE;
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
void RF_Engine::unloadAsset(string id){
    int pos = -1; unsigned int i;
    for(i = 0; i < assetManager.size() && pos == -1; i++)
    {
        if(assetManager[i]->id == id)
        {
            pos = i; //Activamos bandera de salida;
            delete assetManager[i];
            assetManager.erase(assetManager.begin()+pos);
        }
    }
}

SDL_Texture* RF_Engine::getGfx2D(string id){
    //RF_Engine::instance->Debug(("getGfx2D [Info]: " + id));

    Vector2<int> pos = search_in_assetManager(id);
    SDL_Texture* ret = NULL;

    if(pos.y != -1)
    {
        ret = dynamic_cast<RF_Gfx2D*>(assetManager[pos.x]->assets[pos.y])->texture;
        if(ret == NULL)
        {
            ret = SDL_CreateTextureFromSurface(ventana->renderer, dynamic_cast<RF_Gfx2D*>(assetManager[pos.x]->assets[pos.y])->surface);
            dynamic_cast<RF_Gfx2D*>(assetManager[pos.x]->assets[pos.y])->texture = ret;

            RF_Engine::instance->Debug("getGfx2D [Info]: No existía la textura así que se ha creado");
        }
    }

    return ret;
}
SDL_Surface* RF_Engine::getGfx2DSrf(string id){
    Vector2<int> pos = search_in_assetManager(id);
    SDL_Surface* ret = NULL;

    if(pos.y != -1)
    {
        ret = dynamic_cast<RF_Gfx2D*>(assetManager[pos.x]->assets[pos.y])->surface;
    }

    return ret;
}
Mix_Music* RF_Engine::getAudioClip(string id){
    RF_Engine::instance->Debug(("getAudioClip [Info]: " + id));

    Vector2<int> pos = search_in_assetManager(id);

    Mix_Music* ret = NULL;
    if(pos.y != -1)
    {
        ret = dynamic_cast<RF_AudioClip*>(assetManager[pos.x]->assets[pos.y])->clip;
    }

    return ret;
}
Mix_Chunk* RF_Engine::getFXClip(string id){
    RF_Engine::instance->Debug(("getFXClip [Info]: " + id));

    Vector2<int> pos = search_in_assetManager(id);

    Mix_Chunk* ret = NULL;
    if(pos.y != -1)
    {
        ret = dynamic_cast<RF_FXClip*>(assetManager[pos.x]->assets[pos.y])->clip;
    }

    return ret;
}
TTF_Font* RF_Engine::getFont(string id, int pitch){
    Vector2<int> pos = search_in_assetManager(id);

    TTF_Font* ret = NULL;
    if(pos.y != -1)
    {
        if(pitch == -1)
        {
            ret = dynamic_cast<RF_Font*>(assetManager[pos.x]->assets[pos.y])->font;
        }
        else
        {
            ret = TTF_OpenFont(dynamic_cast<RF_Font*>(assetManager[pos.x]->assets[pos.y])->path.c_str(), pitch);
        }
    }

    return ret;
}
Vector2<int> RF_Engine::getMultiSprite_Info(string id){
    Vector2<int> pos = search_in_assetManager((id + "_info"));
    Vector2<int> ret;

    if(pos.y != -1)
    {
        ret = dynamic_cast<RF_MultiSprite_Info*>(assetManager[pos.x]->assets[pos.y])->size;
    }
    else
    {
        ret = pos;
    }

    return ret;
}
RF_Tiled_Map* RF_Engine::getTiledMap(string id){
    Vector2<int> pos = search_in_assetManager(id);

    if(pos.y != -1)
    {
        return dynamic_cast<RF_Tiled_Map*>(assetManager[pos.x]->assets[pos.y]);
    }
    else
    {
        return NULL;
    }

}
void RF_Engine::createTiledSurface(string id){
    RF_Tiled_Map* tMap = RF_Engine::instance->getTiledMap(id);

    if(tMap == NULL) {return;}
    if(tMap->srf != NULL){SDL_FreeSurface(tMap->srf);}

    Vector2<int> lim;
    for(unsigned int i = 0; i < tMap->map->tilesets.size(); i++)
    {
        /**Obtenemos el nombre del fichero sin extensión (que es el id del asset)**/
            string ext = tMap->map->tilesets[i]->filename;
            const size_t pos = ext.find_last_of('.');
            string Aid = ext; Aid.erase(pos);
        /****/
        lim = RF_Engine::instance->getMultiSprite_Info(Aid);

        if(lim.y!=-1)
        {
            for(int jj = 0; jj < lim.y; jj++)
            {
                for(int ii = 0; ii < lim.x; ii++)
                {
                    tMap->realTiles.push_back((Aid + "_" + to_string(ii) + "_" + to_string(jj)));
                }
            }
        }
        else
        {
            tMap->realTiles.push_back(Aid);
        }
    }

    tMap->srf = SDL_CreateRGBSurface(0, tMap->map->width*tMap->map->tileWidth,
                                        tMap->map->height*tMap->map->tileHeight,
                                        RF_Background::instance->screen->format->BitsPerPixel, 0,0,0,0);
    SDL_Surface* tmpSrf;

    for(int i = 0; i < tMap->map->width; i++)
    {
        for(int j = 0; j < tMap->map->height; j++)
        {
            int til = tMap->map->layers[0]->data[j*tMap->map->width + i];
            Uint32 color = 0x000000;

            for(int ii = 0; ii < tMap->map->tileWidth; ii++)
            {
                for(int jj = 0; jj < tMap->map->tileHeight; jj++)
                {
                    if(til > 0)
                    {
                        tmpSrf = RF_Engine::instance->getGfx2DSrf(tMap->realTiles[til-1]);
                        color = RF_Primitive::getPixel(tmpSrf,ii,jj);
                    }

                    RF_Primitive::putPixel(tMap->srf, i*tMap->map->tileWidth + ii, j*tMap->map->tileHeight + jj, color);
                }
            }
        }
    }
}

Vector2<int> RF_Engine::search_in_assetManager(string id){
    int pos = -1; unsigned int i;
    for(i = 0; i < assetManager.size() && pos == -1; i++)
    {
        pos = _search_in_assetManager(i,id);
    }

    return Vector2<int>((int)i-1, pos); //1º Paquete 2º Recurso
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
    int pos = -1;

    if(id > -1){pos = assetManager[id]->assets.size();}

    return pos;
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

    if(collision(ppos1,pscal1,ppos2,pscal2))
    {
        return t;
    }

    return NULL;
}
bool RF_Engine::collision(Vector2<int>ppos1, Vector2<int> pscal1, Vector2<int>ppos2, Vector2<int> pscal2){
    if((ppos1.x+pscal1.x)>ppos2.x && (ppos1.y+pscal1.y)>ppos2.y && (ppos2.x+pscal2.x)>ppos1.x && (ppos2.y+pscal2.y)>ppos1.y)
    {
        return true;
    }

    return false;
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
    /*if(t.scale.x == 0) t.scale.x = 1;
    if(t.scale.y == 0) t.scale.y = 1;*/

    retorno.x=t.position.x + pos.x;// * t.scale.x;
    retorno.y=t.position.y + pos.y;// * t.scale.y;

    /*retorno.x = retorno.x * math->preCos(t.rotation*1000) - retorno.y * math->preSin(t.rotation*1000);
    retorno.y = retorno.y * math->preSin(t.rotation*1000) + retorno.y * math->preCos(t.rotation*1000);*/

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
