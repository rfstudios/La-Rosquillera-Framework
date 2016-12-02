#include "scenetest.h"
#include "protatest.h"
#include "gameobject.h"
#include "rf_soundmanager.h"

void SceneTest::Start()
{
    RF_Engine::instance->Debug(type);
    bg = dynamic_cast<mainProcess*>(RF_Engine::instance->taskManager[father])->bg;

    //RF_SoundManager::playSong("musica", -1);

    pL = new RF_Scroll(0,0);

    pL->newLayer("Pueblo", Vector2<float>(1.0f, 1.0f),Vector2<int>(BLOCK,BLOCK));
    RF_Engine::instance->write("Pulsa WASD para movimiento", {255,255,255}, Vector2<int>(10,RF_Engine::instance->ventana->height()-30));

    pL->setCamera(RF_Engine::instance->newTask(new protatest(),id));
    RF_Engine::instance->newTask(new gameobject(),id);
}

void SceneTest::Update()
{
    //pL->move(50 * RF_Engine::instance->time->deltaTime, 0);

    deltacount+=RF_Engine::instance->time->deltaTime;
    if(deltacount>0.05f)
    {
        deltacount=0.0f;
    }
    return;
}
