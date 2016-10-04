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

    pL = new RF_Parallax_Layer("resources/gfx/logo.png");
    pL->t.position = Vector2<int>(0,0); pL->t.scale = Vector2<int>(3,3); pL->t.rotation=0;
}

void Scene2::Update()
{
    deltacount+=RF_Engine::instance->time->deltaTime;

    if(deltacount>0.01f)
    {
        deltacount=0.0f;
        pL->t.position.x+=5;
        pL->t.position.y = 500 + sin(RF_Engine::instance->time->currentTime*0.002)*500;

        for(int i=0; i<640; i++)
        {
            for(int j=0; j<480; j++)
            {
                bg->putPixel(i,j,pL->getRotoPixel(Vector2<int>(i,j)));
            }
        }
    }
    return;
}

Scene2::~Scene2(){
}
