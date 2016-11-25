#include "scenetest.h"
#include "protatest.h"
#include "gameobject.h"
#include "rf_soundmanager.h"

void SceneTest::Start()
{
    RF_Engine::instance->Debug(type);
    bg = dynamic_cast<mainProcess*>(RF_Engine::instance->taskManager[father])->bg;

    //RF_SoundManager::playSong("musica", -1);

    pL = new RF_Parallax(0,0);

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

        /*Vector2<int> sumPos;
        if(RF_Engine::instance->key[_w])
        {
            sumPos.y = -25;
        }
        else if(RF_Engine::instance->key[_s])
        {
            sumPos.y = 25;
        }

        if(RF_Engine::instance->key[_a])
        {
            sumPos.x = -25;
        }
        else if(RF_Engine::instance->key[_d])
        {
            sumPos.x = 25;
        }

        pL->move(sumPos.x, sumPos.y);
        pL->draw(bg);*/
    }
    return;
}

void SceneTest::metabolas()
{
        metang = M_PI*RF_Engine::instance->time->currentTime*0.000075;
        b1.x=(RF_Engine::instance->ventana->width()/2)+RF_Engine::instance->math->preCos(metang*250000)*150; b1.y=200+RF_Engine::instance->math->preSin(metang*200000)*150;   //b1.z=15;//15
        b2.x=(RF_Engine::instance->ventana->width()/2)+RF_Engine::instance->math->preSin(metang*180000)*150; b2.y=200+RF_Engine::instance->math->preCos(metang*200000)*150; //b2.z=20;//20
        b3.x=(RF_Engine::instance->ventana->width()/2)+RF_Engine::instance->math->preSin((metang+100)*100000)*150; b3.y=200+RF_Engine::instance->math->preCos((metang+50)*100000)*150;  //b3.z=25;//25

        for(i = 0; i < RF_Engine::instance->ventana->width(); i++)
        {
            for(j = 0; j < RF_Engine::instance->ventana->height(); j++)
            {
                if(i < metarange-320 || i > metarange+320)
                {
                    bg->putPixel(i,j,0x000000);
                }
                else if((15/(pow(sqrt(pow(b1.x-i,2)+pow(b1.y-j,2)),0.85)) + 20/(pow(sqrt(pow(b2.x-i,2)+pow(b2.y-j,2)),0.85)) + 25/(pow(sqrt(pow(b3.x-i,2)+pow(b3.y-j,2)),0.85)))<=0.80)
                {
                    bg->putPixel(i,j,0x000000);
                }
            }
        }
}
