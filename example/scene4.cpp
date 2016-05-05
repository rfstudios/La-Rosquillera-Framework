#include "scene4.h"
#include "mainprocess.h"
#include "rf_primitive.h"

void Scene4::Start(){
    bg = dynamic_cast<mainProcess*>(RF_Engine::instance->taskManager[father])->bg;
    SDL_Surface* bgImgS = RF_Engine::instance->loadPNG_Surface("resources/gfx/eBaby.png");
    SDL_Surface* bgImgS2 = RF_Engine::instance->loadPNG_Surface("resources/gfx/logo.png");
    for(int i=0; i<640; i++)
    {
        for(int j=0; j<480; j++)
        {
            bgImg2[i][j] = RF_Primitive::getPixel(bgImgS2,i,j);
            if((i >= 168 && j >= 50) && (i < 471 && j< 430))
            {
                bgImg[i][j] = RF_Primitive::getPixel(bgImgS,i-168,j-50);
            }
            else
            {
                bgImg[i][j] = 0xffffff;
            }
        }
    }
    SDL_FreeSurface(bgImgS);
    SDL_FreeSurface(bgImgS2);
}

void Scene4::Update(){
    deltacount += RF_Engine::instance->time->deltaTime;
    if(0.025f < deltacount)
    {
        /* Rotozoom 1 */
            float angZ1 = M_PI * step * 0.075;
            float crZ1 = cos(angZ1*0.025)*30;
            float srZ1 = sin(angZ1*0.02)*30;

            float sr2Z1=5+(sin(angZ1*0.2)*5)*0.5;

            int xZ1 = crZ1 * cos(step*0.01)*100;
            int yZ1 = srZ1 * sin(step*0.01)*100;

        /* Rotozoom 2 */
            float angZ2 = M_PI * -step * 0.075;
            float crZ2 = cos(angZ2*0.025)*30;
            float srZ2 = sin(angZ2*0.02)*30;

            float sr2Z2=5+(sin(angZ2*0.2)*5)*0.5;

            int xZ2 = crZ2 * cos(step*0.01)*100;
            int yZ2 = srZ2 * sin(step*0.01)*100;

        /* Metabolas */
            float metang = M_PI * step * 0.075;
            Vector3<int> b1, b2, b3;
            b1.x=300+cos(metang*2.5)*150; b1.y=300+sin(metang*2)*150;   b1.z=15;//15
            b2.x=300+sin(metang*1.8)*150; b2.y=300+cos(metang*2.0)*150; b2.z=20;//20
            b3.x=300+sin(metang+100)*150; b3.y=300+cos(metang+50)*150;  b3.z=25;//25

            float radio = 0.80, goo = 0.90;


        for(int i = 0; i < 640; i++)
        {
            for(int j = 0; j < 480; j++)
            {
                int x,y;
                float calcTemp = b1.z/(pow(sqrt(pow(b1.x-i,2)+pow(b1.y-j,2)),goo)) + b2.z/(pow(sqrt(pow(b2.x-i,2)+pow(b2.y-j,2)),goo)) + b3.z/(pow(sqrt(pow(b3.x-i,2)+pow(b3.y-j,2)),goo));

                if(calcTemp > radio)
                {
                    x=(xZ1+abs((int)(i*sr2Z1)))*cos(step*0.01)-(yZ1+abs((int)(j*sr2Z1)))*sin(step*0.01); while(x<0){x+=640;} while(x>639){x-=640;}
                    y=(xZ1+abs((int)(i*sr2Z1)))*sin(step*0.01)+(yZ1+abs((int)(j*sr2Z1)))*cos(step*0.01); while(y<0){y+=480;} while(y>479){y-=480;}

                    if(contB < 1)
                    {
                        bg->putPixel(i,j,bgImg2[x][y]);
                    }
                    else
                    {
                        bg->putPixel(i,j,bgImg[x][y]);
                    }
                }
                else if(calcTemp < radio && calcTemp > radio-0.005)
                {
                    bg->putPixel(i,j,0x010101);
                }
                else
                {
                    x=(xZ2+abs((int)(i*sr2Z2)))*-cos(step*0.01)-(yZ2+abs((int)(j*sr2Z2)))*sin(step*0.01); while(x<0){x+=640;} while(x>639){x-=640;}
                    y=(xZ2+abs((int)(i*sr2Z2)))*-sin(step*0.01)+(yZ2+abs((int)(j*sr2Z2)))*cos(step*0.01); while(y<0){y+=480;} while(y>479){y-=480;}

                    if(contB < 1)
                    {
                        bg->putPixel(i,j,bgImg[x][y]);
                    }
                    else
                    {
                        bg->putPixel(i,j,bgImg2[x][479-y]);
                    }
                }
            }
        }

        step++;
        if(step != 0 && step%30 == 0)
        {
            contB++;
            if(contB>1){contB=0;}
        }

        deltacount = 0.0f;
    }

    if(16800 <= RF_Engine::instance->time->fixedCTime())
    {
        bg->clearSurface(0x000000);
        dynamic_cast<mainProcess*>(RF_Engine::instance->taskManager[father])->state() = 5;
    }
}
