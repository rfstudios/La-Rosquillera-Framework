#include "mainmenu.h"
#include "rf_background.h"
#include "mainprocess.h"

void MainMenu::Start()
{
    RF_Engine::instance->Debug(type);
    bg = dynamic_cast<mainProcess*>(RF_Engine::instance->taskManager[father])->bg;

    pL = new RF_Parallax_Layer("resources/gfx/eBaby.png", Vector2<float>(1.0f, 1.0f), Vector2<int>(REPEAT,NO_REPEAT));
    pL->transform.scale = Vector2<float>(2.0f,2.0f);
    pL->transform.position.x = 5000;
    pL->transform.position.y = RF_Engine::instance->ventana->height();

    texto = RF_Engine::instance->write("Pulsa ENTER para empezar", {0,0,0}, Vector2<int>((RF_Engine::instance->ventana->width()>>1)-250, (RF_Engine::instance->ventana->height()>>1)-100));
}

void MainMenu::Update()
{
        if(RF_Engine::instance->key[_return])
        {
            dynamic_cast<mainProcess*>(RF_Engine::instance->taskManager[father])->state() = 2;
            RF_Engine::instance->deleteText(texto);
            delete pL;

            return;
        }

        pL->transform.position.x -= RF_Engine::instance->math->preCos(RF_Engine::instance->time->currentTime * 100) * 1000 * RF_Engine::instance->time->deltaTime;
        //pL->transform.position.y = RF_Engine::instance->math->preSin(RF_Engine::instance->time->currentTime * 100) * 1000 * RF_Engine::instance->time->deltaTime;
        RF_Engine::instance->Debug(pL->transform.position.x);
        pL->drawAlone(bg);
}
