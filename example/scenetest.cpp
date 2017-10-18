#include "scenetest.h"
#include "protatest.h"
#include "gameobject.h"
#include "rf_soundmanager.h"
#include "rf_3d.h"

void SceneTest::Start()
{
    RF_Engine::instance->Debug(type);
    RF_3D::loadObj("resources/cubo.yawobj");
    RF_Background::instance->prepareSurface();

    //RF_SoundManager::playSong("musica", -1);

    //pL = new RF_Scroll(0,0);

    //RF_Engine::instance->createTiledSurface("prueba");
    //pL->newLayer(RF_Engine::instance->getTiledMap("prueba")->srf, Vector2<float>(1.0f, 1.0f),Vector2<int>(BLOCK,BLOCK));
    //pL->newLayer("Pueblo", Vector2<float>(1.0f, 1.0f),Vector2<int>(BLOCK,BLOCK));
    //RF_Engine::instance->write("Pulsa WASD para movimiento", {255,255,255}, Vector2<int>(10,RF_Engine::instance->ventana->height()-30));

    //pL->setCamera(RF_Engine::instance->newTask(new protatest(),id));
    //RF_Engine::instance->newTask(new gameobject(),id);
}

void SceneTest::Update()
{
    //pL->move(50 * RF_Engine::instance->time->deltaTime, 0);

    deltacount+=RF_Engine::instance->time->deltaTime;
    if(deltacount>0.05f)
    {
        RF_3D::Draw();
        deltacount=0.0f;
    }
    return;
}
