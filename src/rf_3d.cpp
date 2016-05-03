#include "rf_3d.h"
#include "rf_engine.h"
#include "rf_primitive.h"
#include <stdio.h>

vector<RF_3D_Object*> RF_3D::objectList = vector<RF_3D_Object*>();
int RF_3D::_renderMode = RM_Point;

int RF_3D::loadObj(string file)
{
    float aux[4];
    RF_3D_Object* tmpObj = new RF_3D_Object();

    FILE* pf = fopen(file.c_str(),"r");
    if(NULL == pf)
    {
        RF_Engine::instance->Debug("[RF_3D::loadObj] No se ha podido abrir el fichero");
        return -1;
    }

    while(!feof(pf))
    {
        char t[1000];
        fgets(t,1000,pf);
        char dat = t[0];

        int j=0; string tAux;
        for(int i = 0; i < 1000; i++)
        {
            switch(t[i])
            {
                case ' ':
                    aux[j] = atof(tAux.c_str());
                    j++;
                    tAux = "";
                    break;

                case 'v': i++; break;
                case 'f': i++; break;
                default: tAux+=t[i]; break;
            }
        }

        aux[j] = atof(tAux.c_str());

        switch(dat)
        {
            case 'v':
                tmpObj->vertex.push_back(Vector3<float>(aux[0],aux[1],aux[2]));
                break;
            case 'f':
                tmpObj->faces.push_back(Faces((int)aux[0]-1,(int)aux[1]-1,(int)aux[2]-1,(int)aux[3]-1));
                break;
        }
    }

    int siz = tmpObj->vertex.size();

    tmpObj->finalizeCreation();
    RF_3D::objectList.push_back(tmpObj);
    return RF_3D::objectList.size()-1;
}

void RF_3D::Draw_Only(SDL_Surface* screen, int objID)
{
    RF_3D::objectList[objID]->calculateMesh();

    switch(RF_3D::renderMode())
    {
        case RM_Point:
            for(int i=0; i<RF_3D::objectList[objID]->vertex.size();i++)
            {
                RF_Primitive::putPixel(screen, RF_3D::objectList[objID]->vertex[i].x, RF_3D::objectList[objID]->vertex[i].y, 0xffffff);
                RF_Primitive::putPixel(screen, RF_3D::objectList[objID]->vertex[i].x, RF_3D::objectList[objID]->vertex[i].y+1, 0xffffff);
                RF_Primitive::putPixel(screen, RF_3D::objectList[objID]->vertex[i].x+1, RF_3D::objectList[objID]->vertex[i].y, 0xffffff);
                RF_Primitive::putPixel(screen, RF_3D::objectList[objID]->vertex[i].x+1, RF_3D::objectList[objID]->vertex[i].y+1, 0xffffff);
            }
            break;

        case RM_Circles:
            for(int i=0; i<RF_3D::objectList[objID]->vertex.size();i++)
            {
                RF_Primitive::drawCircle(screen,Vector2<int>(RF_3D::objectList[objID]->vertex[i].x,RF_3D::objectList[objID]->vertex[i].y),4,0xffffff);
            }
            break;
        case RM_Mesh:
            for(int i=0; i < RF_3D::objectList[objID]->faces.size(); i++)
            {
                Vector2<int> p0,p1;
                p0.x = RF_3D::objectList[objID]->vertex[RF_3D::objectList[objID]->faces[i].a].x;
                p0.y = RF_3D::objectList[objID]->vertex[RF_3D::objectList[objID]->faces[i].a].y;
                p1.x = RF_3D::objectList[objID]->vertex[RF_3D::objectList[objID]->faces[i].b].x;
                p1.y = RF_3D::objectList[objID]->vertex[RF_3D::objectList[objID]->faces[i].b].y;
                RF_Primitive::drawLine(screen,p0,p1,0xffffff);

                p0.x = RF_3D::objectList[objID]->vertex[RF_3D::objectList[objID]->faces[i].b].x;
                p0.y = RF_3D::objectList[objID]->vertex[RF_3D::objectList[objID]->faces[i].b].y;
                p1.x = RF_3D::objectList[objID]->vertex[RF_3D::objectList[objID]->faces[i].c].x;
                p1.y = RF_3D::objectList[objID]->vertex[RF_3D::objectList[objID]->faces[i].c].y;
                RF_Primitive::drawLine(screen,p0,p1,0xffffff);

                if(RF_3D::objectList[objID]->faces[i].d > -1)
                {
                    p0.x = RF_3D::objectList[objID]->vertex[RF_3D::objectList[objID]->faces[i].c].x;
                    p0.y = RF_3D::objectList[objID]->vertex[RF_3D::objectList[objID]->faces[i].c].y;
                    p1.x = RF_3D::objectList[objID]->vertex[RF_3D::objectList[objID]->faces[i].d].x;
                    p1.y = RF_3D::objectList[objID]->vertex[RF_3D::objectList[objID]->faces[i].d].y;
                    RF_Primitive::drawLine(screen,p0,p1,0xffffff);
                    p0.x = RF_3D::objectList[objID]->vertex[RF_3D::objectList[objID]->faces[i].d].x;
                    p0.y = RF_3D::objectList[objID]->vertex[RF_3D::objectList[objID]->faces[i].d].y;
                    p1.x = RF_3D::objectList[objID]->vertex[RF_3D::objectList[objID]->faces[i].a].x;
                    p1.y = RF_3D::objectList[objID]->vertex[RF_3D::objectList[objID]->faces[i].a].y;
                    RF_Primitive::drawLine(screen,p0,p1,0xffffff);
                }
                else
                {
                    p0.x = RF_3D::objectList[objID]->vertex[RF_3D::objectList[objID]->faces[i].c].x;
                    p0.y = RF_3D::objectList[objID]->vertex[RF_3D::objectList[objID]->faces[i].c].y;
                    p1.x = RF_3D::objectList[objID]->vertex[RF_3D::objectList[objID]->faces[i].a].x;
                    p1.y = RF_3D::objectList[objID]->vertex[RF_3D::objectList[objID]->faces[i].a].y;
                    RF_Primitive::drawLine(screen,p0,p1,0xffffff);
                }
            }
            break;
        case RM_LandScape:
            Uint32 color = 0xff00ff;
            for(int i=0; i<RF_3D::objectList[objID]->vertex.size();i++)
            {
                float z = RF_3D::objectList[objID]->_vertex[i].z;

                if(-0.5f > z)
                {
                    color = 0xff0000;
                }
                else if(-0.5f <= z && -0.2f > z)
                {
                    color = 0xff00ff;
                }
                else if(-0.2f <= z && 0.3f >= z)
                {
                    color = 0xffff00;
                }
                else
                {
                    color = 0x00ffff;
                }

                RF_Primitive::drawFCircle(screen,Vector2<int>(RF_3D::objectList[objID]->vertex[i].x,RF_3D::objectList[objID]->vertex[i].y),2,color);
                /*RF_Primitive::putPixel(screen, RF_3D::objectList[objID]->vertex[i].x, RF_3D::objectList[objID]->vertex[i].y, color);
                RF_Primitive::putPixel(screen, RF_3D::objectList[objID]->vertex[i].x, RF_3D::objectList[objID]->vertex[i].y+1, color);
                RF_Primitive::putPixel(screen, RF_3D::objectList[objID]->vertex[i].x+1, RF_3D::objectList[objID]->vertex[i].y, color);
                RF_Primitive::putPixel(screen, RF_3D::objectList[objID]->vertex[i].x+1, RF_3D::objectList[objID]->vertex[i].y+1, color);*/
            }
            break;
    }

    //return screen;
}
