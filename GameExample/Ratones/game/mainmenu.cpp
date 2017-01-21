#include "mainmenu.h"
#include "mainprocess.h"
#include "raton.h"
#include <SDL2/SDL_image.h>

void MainMenu::Start()
{
    RF_Engine::instance->loadAsset("resources/mainmenu");
    graph = RF_Engine::instance->getGfx2D("mainmenu_background");
    zLayer = 0;

    int b = RF_Engine::instance->newTask(new OptButton("startbutton"),id);
    bt1 = dynamic_cast<OptButton*>(RF_Engine::instance->taskManager[b]);
    bt1->graph = RF_Engine::instance->getGfx2D("startbutton");
    bt1->transform.position = Vector2<float>((RF_Engine::instance->ventana->width()>>1) - 165, (RF_Engine::instance->ventana->height()>>1) - 50);
    bt1->zLayer = 1;

    b = RF_Engine::instance->newTask(new OptButton("exitbutton"),id);
    bt2 = dynamic_cast<OptButton*>(RF_Engine::instance->taskManager[b]);
    bt2->graph = RF_Engine::instance->getGfx2D("exitbutton");
    bt2->transform.position = Vector2<float>((RF_Engine::instance->ventana->width()>>1) - 165, (RF_Engine::instance->ventana->height()>>1) - 50 + 120);
    bt2->zLayer = 1;

}
void MainMenu::Update()
{
    //RF_Engine::instance->Debug((to_string(bt1->transform.position.x) + ", " + to_string(bt1->transform.position.y) + " -> " + to_string(Raton::instance->transform.position.x) + ", " + to_string(Raton::instance->transform.position.y)));
    if(Raton::instance->collision(bt1))
    {
        if(Raton::instance->OnClick)
        {
            if(!checked)
            {
                checked = bt1;
            }
        }
        else
        {
            if(checked == bt1)
            {
                dynamic_cast<mainProcess*>(RF_Engine::instance->taskManager[father])->state() = 2;
            }
        }
    }
    else
    {
        if(checked == bt1)
        {
            checked = NULL;
        }

    }
    if(Raton::instance->collision(bt2))
    {
        if(Raton::instance->OnClick)
        {
            if(!checked)
            {
                checked = bt2;
            }
        }
        else
        {
            if(checked == bt2)
            {
                RF_Engine::instance->isRunning(false);
            }
        }
    }
    else
    {
        if(checked == bt2)
        {
            checked = NULL;
        }

    }
}
