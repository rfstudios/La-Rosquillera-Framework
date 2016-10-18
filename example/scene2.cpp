#include "scene2.h"
#include "mainprocess.h"
#include "rf_declares.h"
#include "rf_primitive.h"
#include "rf_math.h"

#include <math.h>
using namespace std;

void Scene2::Start()
{
    RF_Engine::instance->Debug(type);
    bg = dynamic_cast<mainProcess*>(RF_Engine::instance->taskManager[father])->bg;

    RF_Engine::instance->playSong("resources/musica.mp3");

    pL = new RF_Parallax(0,0);

    pL->newLayer("resources/gfx/hierba_parallax.png", Vector2<float>(1.0f, 1.5f));
    pL->newLayer("resources/gfx/mountain_front_parallax.png", Vector2<float>(1.5f, 1.6f));
    pL->newLayer("resources/gfx/mountain_parallax.png", Vector2<float>(3.0f, 2.0f));
    pL->newLayer("resources/gfx/nubes_parallax.png", Vector2<float>(8.0f, 8.0f));
    pL->newLayer("resources/gfx/fondo_parallax.png", Vector2<float>(12.0f, 12.0f));

    metarange = RF_Engine::instance->ventana->width()>>1;

    RF_Engine::instance->write("Pulsa SPACE para divertimento", {255,255,255}, Vector2<int>(10,RF_Engine::instance->ventana->height()-30));
}

void Scene2::Update()
{
    //pL->move(50 * RF_Engine::instance->time->deltaTime, 0);

    deltacount+=RF_Engine::instance->time->deltaTime;
    if(deltacount>0.05f)
    {
        deltacount=0.0f;

        step+=5;
        pL->position(RF_Engine::instance->time->currentTime * 0.1, -50 + RF_Engine::instance->math->preCos((step)*1000)*200);

        pL->draw(bg);

        if(RF_Engine::instance->key[_space])
        {
            metabolas();
        }
    }
    return;
}

void Scene2::metabolas()
{
        metang = M_PI*RF_Engine::instance->time->currentTime*0.000075;
        b1.x=(RF_Engine::instance->ventana->width()/2)+RF_Engine::instance->math->preCos(metang*250000)*150; b1.y=200+RF_Engine::instance->math->preSin(metang*200000)*150;   //b1.z=15;//15
        b2.x=(RF_Engine::instance->ventana->width()/2)+RF_Engine::instance->math->preSin(metang*180000)*150; b2.y=200+RF_Engine::instance->math->preCos(metang*200000)*150; //b2.z=20;//20
        b3.x=(RF_Engine::instance->ventana->width()/2)+RF_Engine::instance->math->preSin((metang+100)*100000)*150; b3.y=200+RF_Engine::instance->math->preCos((metang+50)*100000)*150;  //b3.z=25;//25

        for(i = 0; i < RF_Engine::instance->ventana->width(); i++)
        {
            for(j = 0; j < RF_Engine::instance->ventana->height(); j++)
            {
                if(i < metarange-320 || i > metarange+320)
                {
                    bg->putPixel(i,j,0x000000);
                }
                else if((15/(pow(sqrt(pow(b1.x-i,2)+pow(b1.y-j,2)),0.85)) + 20/(pow(sqrt(pow(b2.x-i,2)+pow(b2.y-j,2)),0.85)) + 25/(pow(sqrt(pow(b3.x-i,2)+pow(b3.y-j,2)),0.85)))<=0.80)
                {
                    bg->putPixel(i,j,0x000000);
                }
            }
        }
}
