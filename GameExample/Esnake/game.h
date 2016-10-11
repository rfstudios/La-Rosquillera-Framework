#ifndef GAME_H
#define GAME_H

#include <rf_process.h>
#include "rf_parallax_layer.h"
#include "rf_background.h"
#include "rf_declares.h"

#include <vector>
using namespace std;

class Game : public RF_Process
{
    public:
        Game():RF_Process("Game"){}
        virtual ~Game(){}

        virtual void Start();
        virtual void Update();
        void drawRect();

    private:
        float deltaCount = 0.0f;
        RF_Parallax_Layer* pL;
        RF_Background* bg;
        int gamegrid[80][60];

        Vector3<int> snake;
        int snake_direction;

        bool losed = false;
        int shake_x = 0, shake_y = 0, _shake_x = 0, _shake_y = 0, _shake_modifier = 200;
        int effect = 0;
        float effect_timer = -1;
            int effect_limit = 2;

        Vector2<int> dosTextos;

        //Auxiliares
            Vector2<int> rectSize;
            int i,j,ii,jj,fC=0;
            Uint32 color;

        //Funciones de juego
            void InputUpdate();
            void SnakeUpdate();
            void GridUpdate();

            void setFood();
            void shakeCam();
            void handiCam();

            void restart();
};

#endif // GAME_H
