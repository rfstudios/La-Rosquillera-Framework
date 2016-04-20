#include "scene2.h"
#include "mainprocess.h"
#include "rf_declares.h"

#include <math.h>
using namespace std;

void Scene2::Start()
{
    bg = dynamic_cast<mainProcess*>(engine->taskManager[father])->bg;
}

void Scene2::Update()
{
    engine->Debug(engine->time->fixedCTime());
    deltaCount += engine->time->deltaTime;

    if(!lastFrame)
    {
        lastFrame = Starfield(16775);
    }

    ///TODO: Motor3D
    return;
}

bool Scene2::Starfield(int limit)
{
    if(0 == engine->time->fixedCTime()%10)
    {
        if(100 > stars.size())
        {
            int xx = 320 + (rand()%100-50); if(320 == xx){xx = 315;}
            int yy = 240 + (rand()%100-50); if(240 == yy){yy = 235;}
            stars.push_back(Vector2<int>(xx,yy));
            stars_speed.push_back(15 + rand()%11);
        }
    }

    if(0.025f < deltaCount)
    {
        deltaCount = 0.0f;

        bg->clearSurface(0x000000);
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

            if(limit > engine->time->fixedCTime())
            {
                if(0 > xx || 0 > yy || engine->ventana->width() <= xx || engine->ventana->height() <= yy)
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
    }

    return false;
}
