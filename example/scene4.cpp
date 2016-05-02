#include "scene4.h"
#include "mainprocess.h"
#include "rf_primitive.h"

void Scene4::Start(){
    bg = dynamic_cast<mainProcess*>(RF_Engine::instance->taskManager[father])->bg;
    SDL_Surface* bgImgS = RF_Engine::instance->loadPNG_Surface("resources/gfx/eBaby.png");
    for(int i=0; i<640; i++)
    {
        for(int j=0; j<480; j++)
        {
            bgImg[i][j] = RF_Primitive::getPixel(bgImgS,i,j);
        }
    }
    SDL_FreeSurface(bgImgS);
}
void Scene4::Update(){
    deltacount += RF_Engine::instance->time->deltaTime;

    if(0.025 < deltacount)
    {
        float zL = 10.0;

        float ang = M_PI*step*0.075;
        float cr2=cos(ang*0.025)*30;
        float sr2=sin(ang*0.02)*30;

        float sr=5+(sin(ang*0.2)*5)*0.5;

        int xx = cr2 * cos(step*0.01)*100;
        int yy = sr2 * sin(step*0.01)*100;

        for(int i = 0; i < 640; i++)
        {
            for(int j = 0; j < 480; j++)
            {
                int x=(xx+abs((int)(i*sr)))*cos(step*0.01)-(yy+abs((int)(j*sr)))*sin(step*0.01); while(x<0){x+=640;} while(x>639){x-=640;}
                int y=(xx+abs((int)(i*sr)))*sin(step*0.01)+(yy+abs((int)(j*sr)))*cos(step*0.01); while(y<0){y+=480;} while(y>479){y-=480;}
                bg->putPixel(i,j,bgImg[x][y]);
            }
        }

        step++;
        deltacount = 0.0f;
    }
}
