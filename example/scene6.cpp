#include "scene6.h"

#include "mainprocess.h"
#include "rf_3d.h"
#include "rf_3d_object.h"

#include "rf_primitive.h"

void Scene6::Start(){
    RF_Engine::instance->font = TTF_OpenFont("resources/Times_New_Roman.ttf", 30);
    bg = dynamic_cast<mainProcess*>(RF_Engine::instance->taskManager[father])->bg;

    RF_3D_Object* tmpObj = new RF_3D_Object();

    for(float i = -7.5; i < 7.5; i+=0.2)
    {
        for(float j = -7.5; j < 7.5; j+=0.2)
        {
            tmpObj->vertex.push_back(Vector3<float>(i,j,-1.3));
        }
    }

    tmpObj->finalizeCreation();
    tmpObj->transform.position = Vector3<float>(320.0f,240.0f,50.0f);
    tmpObj->transform.rotation = Vector3<float>(64.0f,60.0f,0.0f);
    tmpObj->transform.scale = Vector3<float>(50.0f,50.0f,50.0f);
    RF_3D::objectList.push_back(tmpObj);

    RF_3D::renderMode() = RM_LandScape;

    bezierText("Thank's for watch my first demo.",50);
    bezierText("Programmed in C++ for ",100);
    bezierText("Euskal Encounter 24.",150);

    bezierText("Music by Stage7 - Genshiken ",300);
    bezierText("Code by Yawin ",350);
}

void Scene6::Update(){

    deltaCount += RF_Engine::instance->time->deltaTime;
    if(0.025f < deltaCount)
    {
        bg->clearSurface(0x000000);

        for(int i = 0; i < RF_3D::objectList[0]->_vertex.size(); i++)
        {
            float x = RF_3D::objectList[0]->_vertex[i].x * RF_3D::objectList[0]->_vertex[i].y;
            RF_3D::objectList[0]->_vertex[i].z = -1.3 + cos((step+x)*0.05)*2.5;
        }

        SDL_Surface* tmpSrf = SDL_CreateRGBSurface(0,RF_Engine::instance->ventana->width(), RF_Engine::instance->ventana->height(),32,0,0,0,0);
        RF_3D::Draw_Only(tmpSrf, 0);
        bg->addSurface(tmpSrf);
        SDL_FreeSurface(tmpSrf);

        step++;
        deltaCount = 0.0f;
    }
}

void Scene6::bezierText(string text, int y){
    int x = 620;

    for(int i = text.length()-1; i >= 0 ; i--)
    {

        if(text.length() - 1 > i)
        {
            if(text.substr(i,1) == " ")
            {
                x+=5;
            }
            else if(text.substr(i,1) == "m")
            {
                x-=8;
            }
            else if(text.substr(i,1) == "s")
            {
                x+=3;
            }
            else if(text.substr(i,1) == "r")
            {
                x+=3;
            }
            else if(text.substr(i,1) == "i")
            {
                x+=5;
            }
            else if(text.substr(i,1) == "h")
            {
                x-=2;
            }
            else if(text.substr(i,1) == "I")
            {
                x+=3;
            }
            else if(text.substr(i,1) == "T")
            {
                x-=5;
            }
            else if(text.substr(i,1) == "t")
            {
                x+=5;
            }
            else if(text.substr(i,1) == "'")
            {
                x+=7;
            }
            else if(text.substr(i,1) == "l")
            {
                x+=4;
            }
            else if(text.substr(i,1) == "w")
            {
                x-=5;
            }
            else if(text.substr(i,1) == "G")
            {
                x-=8;
            }
            else if(text.substr(i,1) == "M")
            {
                x-=12;
            }
            else if(text.substr(i,1) == "P")
            {
                x-=2;
            }
            else if(text.substr(i,1) == "C")
            {
                x-=5;
            }
            else if(text.substr(i,1) == "E")
            {
                x-=3;
            }
        }

        RF_Engine::instance->newTask(new BezierLetter(text.substr(i,1),Vector2<int>(x,y),i),id);

        x -= 15;
    }
}

void BezierLetter::Update(){

    deltaCount+=RF_Engine::instance->time->deltaTime;
    if(0.025 < deltaCount && 0 <= step)
    {
        if(-1 < textID && NULL != RF_Engine::instance->textSources[textID])
        {
            RF_Engine::instance->deleteText(textID);
        }

        if(100 >= step)
        {
            deltaCount = 0.0f;

            float beziert = step * 0.01;
            x = position.x*(1-beziert)*(pow(1-beziert,2)+5*pow(beziert,2));
            y = position.y*(pow(1-beziert,3)+pow(beziert,3))+(y-50)*3*(beziert-pow(beziert,2));
        }
        textID = RF_Engine::instance->write(text, {255,255,255}, Vector2<int>(x, y));

        step--;
    }
}
