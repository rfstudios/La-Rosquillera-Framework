#include "scenetest.h"
#include "protatest.h"
#include "gameobject.h"
#include "rf_soundmanager.h"
#include "rf_3d.h"

void SceneTest::Start()
{
    RF_Engine::instance->Debug(type);
    RF_3D::loadObj("resources/cubo.yawobj");
    RF_3D::loadObj("resources/ico.yawobj");
    RF_Background::instance->prepareSurface();

    Transform3D t(Vector3<float>(250.0f,350.0f,240.0f),Vector3<float>(0.0f,0.0f,0.0f),Vector3<float>(50.0f,50.0f,50.0f));
    RF_3D::objectList[0]->transform = t;
    RF_3D::objectList[1]->transform = t;
    RF_3D::objectList[0]->transform.position.x = 750.0f;
    RF_3D::objectList[1]->transform.position.y = 400.0f;

    RF_3D::renderMode() = RM_Mesh;

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
        RF_3D::objectList[0]->transform.rotation.x += 0.05;
        RF_3D::objectList[0]->transform.rotation.y += 0.15;
        RF_3D::objectList[0]->transform.position.x += RF_Engine::instance->math->preCos(RF_Engine::instance->time->currentTime*100)*15;
        RF_3D::objectList[0]->transform.position.y += RF_Engine::instance->math->preSin(RF_Engine::instance->time->currentTime*100)*15;

        RF_3D::objectList[1]->transform.rotation.x += 0.15;
        RF_3D::objectList[1]->transform.rotation.y += 0.05;
        RF_3D::objectList[1]->transform.position.x += RF_Engine::instance->math->preSin(RF_Engine::instance->time->currentTime*100)*15;
        RF_3D::objectList[1]->transform.position.y += RF_Engine::instance->math->preCos(RF_Engine::instance->time->currentTime*100)*15;

        float s = RF_3D::objectList[0]->transform.scale.x + RF_Engine::instance->math->preSin(RF_Engine::instance->time->currentTime*200)*10;
        float s2 = RF_3D::objectList[1]->transform.scale.x + RF_Engine::instance->math->preCos(RF_Engine::instance->time->currentTime*200)*10;
        if(s < 50.0f){s = 50.0f;}
        if(s2 < 50.0f){s2 = 50.0f;}

        RF_3D::objectList[0]->transform.scale.x = RF_3D::objectList[0]->transform.scale.y = RF_3D::objectList[0]->transform.scale.z = s;
        RF_3D::objectList[1]->transform.scale.x = RF_3D::objectList[1]->transform.scale.y = RF_3D::objectList[1]->transform.scale.z = s2;
        RF_Background::instance->clearSurface(0x000000);
        SDL_Surface *tmpSrf = SDL_CreateRGBSurface(0,RF_Engine::instance->ventana->width(), RF_Engine::instance->ventana->height(),32,0,0,0,0);

        if(s > 75 && s < 120){RF_3D::renderMode() = RM_Circles;}
        else if(s > 120){RF_3D::renderMode() = RM_Point;}
        else {RF_3D::renderMode() = RM_Mesh;}
        RF_3D::Draw_Only(tmpSrf, 0);

        if(s2 > 75 && s2 < 120){RF_3D::renderMode() = RM_Circles;}
        else if(s2 > 120){RF_3D::renderMode() = RM_Point;}
        else {RF_3D::renderMode() = RM_Mesh;}
        RF_3D::Draw_Only(tmpSrf, 1);

        deltacount=0.0f;
        RF_Background::instance->addSurface(tmpSrf);
        SDL_FreeSurface(tmpSrf);
    }
    return;
}
