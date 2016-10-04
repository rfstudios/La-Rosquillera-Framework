#include "scene2.h"
#include "mainprocess.h"
#include "rf_declares.h"
#include "rf_primitive.h"

#include <math.h>
using namespace std;

void Scene2::Start()
{
    RF_Engine::instance->Debug(type);
    bg = dynamic_cast<mainProcess*>(RF_Engine::instance->taskManager[father])->bg;

    pL = new RF_Parallax(0,0);

    pL->newLayer("resources/gfx/hierba_parallax.png", Vector2<float>(0.5f, 0.5f));
    pL->newLayer("resources/gfx/mountain_front_parallax.png", Vector2<float>(2.0f, 2.0f));
    pL->newLayer("resources/gfx/mountain_parallax.png", Vector2<float>(3.0f, 3.0f));
    pL->newLayer("resources/gfx/nubes_parallax.png", Vector2<float>(8.0f, 8.0f));
    pL->newLayer("resources/gfx/fondo_parallax.png", Vector2<float>(12.0f, 12.0f));
}

void Scene2::Update()
{
    deltacount+=RF_Engine::instance->time->deltaTime;

    if(deltacount>0.05f)
    {
        deltacount=0.0f;
        //pL->position(RF_Engine::instance->time->currentTime * 0.1, cos(pL->transform.position.x*0.1)*30);
        pL->position(RF_Engine::instance->time->currentTime * 0.1, 0);

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
        b1.x=300+cos(metang*2.5)*150; b1.y=200+sin(metang*2)*150;   //b1.z=15;//15
        b2.x=300+sin(metang*1.8)*150; b2.y=200+cos(metang*2.0)*150; //b2.z=20;//20
        b3.x=300+sin(metang+100)*150; b3.y=200+cos(metang+50)*150;  //b3.z=25;//25

        for(i = 0; i < 640; i++)
        {
            for(j = 0; j < 480; j++)
            {
                if((15/(pow(sqrt(pow(b1.x-i,2)+pow(b1.y-j,2)),0.85)) + 20/(pow(sqrt(pow(b2.x-i,2)+pow(b2.y-j,2)),0.85)) + 25/(pow(sqrt(pow(b3.x-i,2)+pow(b3.y-j,2)),0.85)))<=0.80)
                {
                    bg->putPixel(i,j,0x000000);
                }
            }
        }
}
