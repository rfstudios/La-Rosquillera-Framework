#include "scenetest.h"
#include "rf_soundmanager.h"

void SceneTest::Start()
{
    RF_Engine::instance->Debug(type);
    bg = dynamic_cast<mainProcess*>(RF_Engine::instance->taskManager[father])->bg;

    bg->clearSurface(0x000000);

    assetCont = RF_Engine::instance->assetCount("gfx");
    RF_SoundManager::playFX("w2_robots");

    RF_Engine::instance->font = RF_Engine::instance->getFont("Times_New_Roman");
    RF_Engine::instance->write("Cacapito", {255,255,255}, Vector2<int>(RF_Engine::instance->ventana->width()>>1, RF_Engine::instance->ventana->height()-200));
}

void SceneTest::Update()
{
    deltacount += RF_Engine::instance->time->deltaTime;

    if(deltacount >= 1.0f)
    {
        deltacount = 0.0f;

        cont++; if(cont >= assetCont){cont = 0;}

        switch(cont)
        {
            case 0:
                graph = RF_Engine::instance->getGfx2D("demoordie");
                break;
            case 1:
                graph = RF_Engine::instance->getGfx2D("eBaby");
                break;
            case 2:
                graph = RF_Engine::instance->getGfx2D("euskal");
                break;
            case 3:
                graph = RF_Engine::instance->getGfx2D("logo");
                break;
            case 4:
                graph = RF_Engine::instance->getGfx2D("fondo_parallax");
                break;
            case 5:
                graph = RF_Engine::instance->getGfx2D("hierba_parallax");
                break;
            case 6:
                graph = RF_Engine::instance->getGfx2D("mountain_front_parallax");
                break;
            case 7:
                graph = RF_Engine::instance->getGfx2D("mountain_parallax");
                break;
            case 8:
                graph = RF_Engine::instance->getGfx2D("nubes_parallax");
                //RF_SoundManager::changeMusic("musica");
                break;
        }
    }
}
