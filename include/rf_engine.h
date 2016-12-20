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
#include "rf_math.h"
#include "rf_asset_list.h"
#include "rf_asset.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include <vector>
#include <iostream>
#include <stdio.h>
using namespace std;

class RF_Engine
{
    public:
        static RF_Engine* instance;

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
            int getPlace();
            void manageSignals();
            void sendSignal(unsigned int task, int signal);
            void sendSignal(string type, int signal);
            bool exists(string type);
        /************************************/

        SDL_Event event;    //Evento para controlar teclado
        bool key[_FOO_KEY]; //Array de teclas pulsadas
        RF_Time *time;

        /**Textos*****************/
            TTF_Font* font;
            vector<YW_Text*> textSources;
            int write(string txt, SDL_Color color, Vector2<int> pos);
            int write(string txt, SDL_Color color, Vector2<float> pos);
            int _writeGetPlace();
            void deleteText(int txtID = -1);
        /*************************/

        /**Control de debug*******/
            bool isDebug;
            void Debug(string t);
            void Debug(int t);
            void Debug(float t);
        /*************************/

        /**Assets****************/
            vector<RF_Asset_List*> assetManager;
            void loadAsset(string path);
            void unloadAsset(string id);
            SDL_Surface* getGfx2DSrf(string id);
            SDL_Texture* getGfx2D(string id);
            Mix_Music* getAudioClip(string id);
            Mix_Chunk* getFXClip(string id);
            TTF_Font* getFont(string id, int pitch = -1);
            Vector2<int> getMultiSprite_Info(string id);
            RF_Tiled_Map* getTiledMap(string id);
            void createTiledSurface(string id);
            Vector2<int> search_in_assetManager(string id);
            int _search_in_assetManager(int i, string id);
            int assetCount(string id);
            int assetCount(int id);
        /*************************/

        /**Utilidades************/
            SDL_Surface* loadPNG_Surface(string file);
            SDL_Texture* loadPNG(string file);
            RF_Process* collision(string target, RF_Process* sender);
            RF_Process* collision(int target, RF_Process* sender);

            RF_Math* math;

            Vector2<int> rotozoom(Vector2<int> pos, Transform2D<int> t, Vector2<int> lim, Vector2<bool> mirror = Vector2<bool>(true,true));
                Vector2<int> retorno;
        /************************/
    private:
};

#endif // RF_ENGINE_H
