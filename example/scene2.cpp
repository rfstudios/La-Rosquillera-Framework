#include "scene2.h"
#include "mainprocess.h"
#include "rf_declares.h"
#include "rf_3d.h"

#include <math.h>
using namespace std;

void Scene2::Start()
{
    RF_Engine::instance->Debug(type);

    bg = dynamic_cast<mainProcess*>(RF_Engine::instance->taskManager[father])->bg;
    RF_3D::loadObj("resources/ico.yawobj");
    RF_3D::loadObj("resources/cubo.yawobj");

    Transform3D t(Vector3<float>(213.0f,240.0f,240.0f),Vector3<float>(0.0f,0.0f,0.0f),Vector3<float>(50.0f,50.0f,50.0f));
    RF_3D::objectList[0]->transform = t;

    t.position.x = 426;
    RF_3D::objectList[1]->transform = t;

    RF_3D::renderMode() = RM_Mesh;
}

void Scene2::Update()
{
    deltaCount += RF_Engine::instance->time->deltaTime;

    if(0.025f < deltaCount)
    {
        bg->clearSurface(0x000000);
        step++;

        tmpSrf = SDL_CreateRGBSurface(0,RF_Engine::instance->ventana->width(), RF_Engine::instance->ventana->height(),32,0,0,0,0);

        for(int i=0; i<RF_3D::objectList.size(); i++)
        {
            RF_3D::objectList[i]->transform.rotation.x += 0.05;
            RF_3D::objectList[i]->transform.rotation.z += 0.05;

            RF_3D::Draw_Only(tmpSrf, i);
        }

        bg->addSurface(tmpSrf);
        SDL_FreeSurface(tmpSrf);

        deltaCount = 0.0f;
    }
    return;
}

Scene2::~Scene2(){
    RF_3D::objectList.clear();
}
