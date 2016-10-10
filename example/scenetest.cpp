#include "scenetest.h"

void SceneTest::Start()
{
    RF_Engine::instance->Debug(type);
    bg = dynamic_cast<mainProcess*>(RF_Engine::instance->taskManager[father])->bg;
    pL = new RF_Parallax_Layer("resources/gfx/eBaby.png", Vector2<float>(1.0f, 1.0f), Vector2<bool>(true,true));
    /*pL->transform.position.x = 3 * bg->screen->w>>1;
    pL->transform.position.y = 3 * bg->screen->h>>1;*/
    pL->transform.scale.x = pL->transform.scale.y = 3.0f;

    bg->clearSurface(0xFFFFFF);

    /*for(int i = 0; i < RF_Engine::instance->ventana->width(); i++)
    {
        bg->putPixel(i, 240 + RF_Engine::instance->math->preCos(i*1000,true)*100, 0xFFFFFF);
        bg->putPixel(i, 240 + RF_Engine::instance->math->preSin(i*1000,false)*100, 0xFF0000);
    }*/
}

void SceneTest::Update()
{
        pL->transform.position.x += RF_Engine::instance->math->preCos(RF_Engine::instance->time->currentTime*100)*50;
        pL->transform.position.y += RF_Engine::instance->math->preSin(RF_Engine::instance->time->currentTime*100)*50;

        pL->transform.scale.x = pL->transform.scale.y = RF_Engine::instance->math->preCos(RF_Engine::instance->time->currentTime*50)*10;
        if(pL->transform.scale.x < 0){pL->transform.scale.x = -pL->transform.scale.x;}
        if(pL->transform.scale.y < 0){pL->transform.scale.y = -pL->transform.scale.y;}

        pL->drawAlone(bg);
}
