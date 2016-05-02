#include "scene2.h"
#include "mainprocess.h"
#include "rf_declares.h"
#include "rf_3d.h"

#include <math.h>
using namespace std;

void Scene2::Start()
{
    RF_Engine::instance->font = TTF_OpenFont("resources/Purisa.ttf", 20);
    bg = dynamic_cast<mainProcess*>(RF_Engine::instance->taskManager[father])->bg;
    RF_3D::loadObj("resources/ico.yawobj");
    RF_3D::loadObj("resources/cubo.yawobj");

    Transform3D t(Vector3<float>(320.0f,240.0f,240.0f),Vector3<float>(0.0f,0.0f,0.0f),Vector3<float>(50.0f,50.0f,50.0f));
    RF_3D::objectList[0]->transform = t;
    RF_3D::objectList[1]->transform = t;
}

void Scene2::Update()
{
    deltaCount += RF_Engine::instance->time->deltaTime;

    if(0.025f < deltaCount)
    {
        bg->clearSurface(0x000000);
        step++; step2++;

        if(!lastFrame && cuentaobj == 0)
        {
            lastFrame = Starfield(16775);
        }

        if(16800 < RF_Engine::instance->time->fixedCTime())
        {
            if(cuentaobj>4)
            {
                lastFrame = Starfield(60000);
            }

            Transform3D tmpT = RF_3D::objectList[0]->transform;

            int tmpScl = cos(step*0.025) * 500;
            if(50 > tmpScl){tmpScl = 50;}

            if(50 == tmpScl)
            {
                RF_3D::renderMode() = RM_Mesh;
                cH = false;
            }
            else
            {
                RF_3D::renderMode() = RM_Circles;

                if(tmpScl > 400 && cH == false)
                {
                    cuentaobj++;
                    cH=true;
                    if(cuentaobj>2)
                    {
                        if(cuentaobj%2==0)
                        {
                            objtorend=0;
                        }
                        else
                        {
                            objtorend=1;
                        }
                    }
                }
            }

            tmpT.scale.x = tmpT.scale.y = tmpT.scale.z = tmpScl;
            tmpT.rotation.x += 0.05; tmpT.rotation.y += 0.055;//tmpT.scale.z = tmpScl;

            RF_3D::objectList[0]->transform = RF_3D::objectList[1]->transform = tmpT;

            SDL_Surface* tmpSrf = SDL_CreateRGBSurface(0,RF_Engine::instance->ventana->width(), RF_Engine::instance->ventana->height(),32,0,0,0,0);
            RF_3D::Draw_Only(tmpSrf, objtorend);
            bg->addSurface(tmpSrf);
            SDL_FreeSurface(tmpSrf);

            if(step2 > 100)
            {
                switch(textcont)
                {
                    case 0:
                        Scrolltext("Stage7 Genshiken", 100);
                        break;
                    case 1:
                        Scrolltext("Achifaifa", 400);
                        break;
                    case 2:
                        stars.clear();
                        stars_speed.clear();
                        Scrolltext("Marcan", 300);
                        break;
                    case 3:
                        Scrolltext("Freddy Soga", 400);
                        break;
                    case 4:
                        Scrolltext("Imobilis", 250);
                        break;
                    case 5:
                        Scrolltext("Klondike", 150);
                        break;
                    case 6:
                        Scrolltext("Zeru", 315);
                        break;
                    case 7:
                        Scrolltext("Red&Zuzu", 75);
                        break;
                    case 8:
                        Scrolltext("A.J.Y", 350);
                        break;
                }
                textcont++;
                step2=0;
            }
        }

        deltaCount = 0.0f;
    }

    if(55078 <= RF_Engine::instance->time->fixedCTime())
    {
        bg->clearSurface(0x000000);
        dynamic_cast<mainProcess*>(RF_Engine::instance->taskManager[father])->state() = 3;
    }
    return;
}

bool Scene2::Starfield(int limit){
    if(100 > stars.size())
    {
        int xx = 320 + (rand()%100-50); if(320 == xx){xx = 315;}
        int yy = 240 + (rand()%100-50); if(240 == yy){yy = 235;}
        stars.push_back(Vector2<int>(xx,yy));
        stars_speed.push_back(15 + rand()%11);
    }

    bool painted = false;
    for(int i = 0; i < stars.size(); i++)
    {
        int xx = stars[i].x -( round(320 - stars[i].x) / stars_speed[i]);
        int yy = stars[i].y -( round(240 - stars[i].y) / stars_speed[i]);

        if(xx == stars[i].x && yy == stars[i].y)
        {
            xx = 320 + (rand()%100-50); if(320 == xx){xx = 315;}
            yy = 240 + (rand()%100-50); if(240 == yy){yy = 235;}
        }

        int dist = abs(xx - 320) + abs(yy - 240);
        int sCant;

        if(dist < 50)
        {
            sCant = 1;
        }
        else if(dist >= 50 && dist <= 100)
        {
            sCant = 2;
        }
        else if(dist >= 100 && dist <= 150)
        {
            sCant = 3;
        }
        else if(dist >= 150 && dist <= 200)
        {
            sCant = 4;
        }
        else if(dist > 200)
        {
            sCant = 5;
        }

        for(int i = 0; i < sCant; i++)
        {
            for(int j = 0; j < sCant; j++)
            {
                bg->putPixel(xx+i, yy+j, 0xffffff);
                painted = true;
            }
        }

        if(limit > RF_Engine::instance->time->fixedCTime())
        {
            if(0 > xx || 0 > yy || RF_Engine::instance->ventana->width() <= xx || RF_Engine::instance->ventana->height() <= yy)
            {
                xx = 320 + (rand()%100-50); if(320 == xx){xx = 315;}
                yy = 240 + (rand()%100-50); if(240 == yy){yy = 235;}
            }
        }

        stars[i].x = xx;
        stars[i].y = yy;
    }

    if(!painted)
    {
        stars.clear();
        stars_speed.clear();

        return true;
    }

    return false;
}
void Scene2::Scrolltext(string text, int y){
    int x = 643;
    for(int i=0;i<text.length();i++)
    {
        RF_Engine::instance->newTask(new scrLetra(text.substr(i,1),Vector2<int>(x,y)),id);
        x+=20;
    }
}

void scrLetra::Update(){
    if(-1 < textID && NULL != RF_Engine::instance->textSources[textID])
    {
        RF_Engine::instance->deleteText(textID);
    }

    textID = RF_Engine::instance->write(txt, {255,255,255}, Vector2<int>((int)pos.x, (int)(pos.y + cos(pos.x*0.05)*30)));
    pos.x-=RF_Engine::instance->time->deltaTime*100;

    if(-10 > pos.x){signal = S_KILL;}
}
