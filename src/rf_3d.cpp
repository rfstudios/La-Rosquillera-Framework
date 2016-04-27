#include "rf_3d.h"
#include "rf_engine.h"
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
                tmpObj->faces.push_back(Faces((int)aux[0],(int)aux[1],(int)aux[2],(int)aux[3]-1));
                break;
        }
    }

    int siz = tmpObj->vertex.size();

    tmpObj->finalizeCreation();
    RF_3D::objectList.push_back(tmpObj);
    return RF_3D::objectList.size()-1;
}

SDL_Surface* RF_3D::Draw_Only(int objID)
{
    RF_Engine::instance->Debug("DrawOnly");
    SDL_Surface* screen = SDL_CreateRGBSurface(0,RF_Engine::instance->ventana->width(), RF_Engine::instance->ventana->height(),32,0,0,0,0);
    RF_3D::objectList[objID]->calculateMesh();

    switch(RF_3D::renderMode())
    {
        case RM_Point:
            for(int i=0; i<RF_3D::objectList[objID]->vertex.size();i++)
            {
                RF_Engine::instance->putPixel(screen, RF_3D::objectList[objID]->vertex[i].x, RF_3D::objectList[objID]->vertex[i].y, 0xffffff);
                //if(i==0){RF_Engine::instance->Debug("Coords"); RF_Engine::instance->Debug(RF_3D::objectList[objID]->vertex[i].x); RF_Engine::instance->Debug(RF_3D::objectList[objID]->vertex[i].y);}
            }
            break;

        case RM_Circles:
            break;
        case RM_Mesh:
            for(int i=0; RF_3D::objectList[objID]->faces.size(); i++)
            {
                //draw_line(cfinales[caras[i][0]][0],cfinales[caras[i][0]][1],cfinales[caras[i][1]][0],cfinales[caras[i][1]][1]);
                //draw_line(cfinales[caras[i][1]][0],cfinales[caras[i][1]][1],cfinales[caras[i][2]][0],cfinales[caras[i][2]][1]);
                //if(caras[i][3]>-1)
                //  draw_line(cfinales[caras[i][2]][0],cfinales[caras[i][2]][1],cfinales[caras[i][3]][0],cfinales[caras[i][3]][1]);
                //  draw_line(cfinales[caras[i][3]][0],cfinales[caras[i][3]][1],cfinales[caras[i][0]][0],cfinales[caras[i][0]][1]);
                //else
                //  draw_line(cfinales[caras[i][2]][0],cfinales[caras[i][2]][1],cfinales[caras[i][0]][0],cfinales[caras[i][0]][1]);
                //end

            }
            break;
    }

    return screen;
}
