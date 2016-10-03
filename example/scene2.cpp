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

    SDL_Surface* bgImgS = RF_Engine::instance->loadPNG_Surface("resources/gfx/logo.png");
    for(int i=0; i<640; i++)
    {
        for(int j=0; j<480; j++)
        {
            bgImg[i][j] = RF_Primitive::getPixel(bgImgS,i,j);
        }
    }
    SDL_FreeSurface(bgImgS);

    t.position = Vector2<int>(0,0); t.scale = Vector2<int>(3,3); t.rotation=0;
}

void Scene2::Update()
{
    deltacount+=RF_Engine::instance->time->deltaTime;

    if(deltacount>0.01f)
    {
        deltacount=0.0f;
        t.position.x+=5;
        t.position.y = 500 + sin(RF_Engine::instance->time->currentTime*0.002)*500;

        for(int i=0; i<640; i++)
        {
            for(int j=0; j<480; j++)
            {
                Vector2<int> tmp = RF_Engine::instance->rotozoom(Vector2<int>(i,j), t);
                bg->putPixel(i,j,bgImg[tmp.x][tmp.y]);
            }
        }
    }
    return;
}

Scene2::~Scene2(){
}
