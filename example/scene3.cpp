#include "scene3.h"
#include "rf_primitive.h"
#include "mainprocess.h"

void Scene3::Start(){
    RF_Engine::instance->Debug(type);

    bg = dynamic_cast<mainProcess*>(RF_Engine::instance->taskManager[father])->bg;
    SDL_Surface* bgImgS = RF_Engine::instance->loadPNG_Surface("resources/gfx/euskal.png");
    for(int i=0; i<640; i++)
    {
        for(int j=0; j<480; j++)
        {
            bgImg[i][j] = RF_Primitive::getPixel(bgImgS,i,j);
        }
    }

    bgImgS = RF_Engine::instance->loadPNG_Surface("resources/gfx/demoordie.png");
    for(int i=0; i<640; i++)
    {
        for(int j=0; j<480; j++)
        {
            bgImg2[i][j] = RF_Primitive::getPixel(bgImgS,i,j);
        }
    }

    SDL_FreeSurface(bgImgS);
}
void Scene3::Update(){
    deltaCont += RF_Engine::instance->time->deltaTime;
    if(deltaCont > 0.025f)
    {
        if(8000 > RF_Engine::instance->time->fixedCTime())
        {
            metaballs(0);
        }
        else
        {
            metaballs(ballC);

            if(0 == step%30)
            {
                ballC++; if(ballC > 2){ballC=1;}
            }

            if(16800 < RF_Engine::instance->time->fixedCTime())
            {
                bg->clearSurface(0x000000);
                dynamic_cast<mainProcess*>(RF_Engine::instance->taskManager[father])->state() = 4;
            }
        }


        step++;
        deltaCont = 0;
    }
}

void Scene3::metaballs(int type){
    float metang = M_PI*step*0.075;
    bg->clearSurface(0x000000);

    Vector3<int> b1, b2, b3;
    b1.x=300+cos(metang*2.5)*150; b1.y=300+sin(metang*2)*150;   b1.z=15;//15
    b2.x=300+sin(metang*1.8)*150; b2.y=300+cos(metang*2.0)*150; b2.z=20;//20
    b3.x=300+sin(metang+100)*150; b3.y=300+cos(metang+50)*150;  b3.z=25;//25

    float radio = 0.80, goo = 0.90;

    for(int i = 0; i < 640; i++)
    {
        for(int j = 0; j < 480; j++)
        {
            if((b1.z/(pow(sqrt(pow(b1.x-i,2)+pow(b1.y-j,2)),goo)) + b2.z/(pow(sqrt(pow(b2.x-i,2)+pow(b2.y-j,2)),goo)) + b3.z/(pow(sqrt(pow(b3.x-i,2)+pow(b3.y-j,2)),goo)))>radio)
            {
                Uint8 r,g,b;
                switch(type)
                {
                    case 0:
                        bg->putPixel(i,j,bgImg[i][j]);
                        break;
                    case 1:
                        bg->putPixel(i,j,bgImg[i][j]);
                        break;
                    case 2:
                        bg->putPixel(i,j,bgImg2[i][j]);
                        break;
                }
            }
            else
            {
                if(0 < type)
                {
                    if(type == 1)
                    {
                        bg->putPixel(i,j,bgImg2[i][j]);
                    }
                    else
                    {
                        bg->putPixel(i,j,bgImg[i][j]);
                    }
                }
            }
        }
    }
}
