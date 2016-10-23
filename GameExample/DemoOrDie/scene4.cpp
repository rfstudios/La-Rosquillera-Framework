#include "scene4.h"
#include "mainprocess.h"
#include "rf_primitive.h"

void Scene4::Start(){
    RF_Engine::instance->Debug(type);

    bg = dynamic_cast<mainProcess*>(RF_Engine::instance->taskManager[father])->bg;
    SDL_Surface* bgImgS = RF_Engine::instance->getGfx2DSrf("eBaby");
    SDL_Surface* bgImgS2 = RF_Engine::instance->getGfx2DSrf("logo");
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
}

void Scene4::Update(){
    deltacount += RF_Engine::instance->time->deltaTime;
    if(0.025f < deltacount)
    {
        /* Rotozoom 1 */
            metang = M_PI * step * 0.075;
            crZ1 = cos(metang*0.025)*30;
            srZ1 = sin(metang*0.02)*30;

            sr2Z1=5+(sin(metang*0.2)*5)*0.5;

            xZ1 = crZ1 * cos(step*0.01)*100;
            yZ1 = srZ1 * sin(step*0.01)*100;

        /* Rotozoom 2 */
            crZ2 = cos(-metang*0.025)*30;
            srZ2 = sin(-metang*0.02)*30;

            sr2Z2=5+(sin(-metang*0.2)*5)*0.5;

            xZ2 = crZ2 * cos(step*0.01)*100;
            yZ2 = srZ2 * sin(step*0.01)*100;

        /* Metabolas */
            b1.x=300+cos(metang*2.5)*150; b1.y=300+sin(metang*2)*150;   b1.z=15;//15
            b2.x=300+sin(metang*1.8)*150; b2.y=300+cos(metang*2.0)*150; b2.z=20;//20
            b3.x=300+sin(metang+100)*150; b3.y=300+cos(metang+50)*150;  b3.z=25;//25

        for(int i = 0; i < 640; i++)
        {
            calci1 = pow(b1.x-i,2);
            calci2 = pow(b2.x-i,2);
            calci3 = pow(b3.x-i,2);

            calc12 = xZ2+abs((int)(i*sr2Z2));
            calc11 = xZ1+abs((int)(i*sr2Z1));
            calc32 = calc12+abs((int)(i*sr2Z2));

            for(int j = 0; j < 480; j++)
            {
                calcTemp = b1.z/(pow(sqrt(calci1+pow(b1.y-j,2)),0.90)) + b2.z/(pow(sqrt(calci2+pow(b2.y-j,2)),0.90)) + b3.z/(pow(sqrt(calci3+pow(b3.y-j,2)),0.90));

                if(calcTemp > 0.80)
                {
                    calc21 = yZ1+abs((int)(j*sr2Z1));

                    x=(calc11)*cos(step*0.01)-(calc21)*sin(step*0.01); while(x<0){x+=640;} while(x>639){x-=640;}
                    y=(calc11)*sin(step*0.01)+(calc21)*cos(step*0.01); while(y<0){y+=480;} while(y>479){y-=480;}

                    bg->putPixel(i,j,bgImg2[x][y]);
                }
                else if(calcTemp < 0.80 && calcTemp > 0.795)
                {
                    bg->putPixel(i,j,0x010101);
                }
                else
                {
                    calc22 = yZ2+abs((int)(j*sr2Z2));

                    x=(calc12)*-cos(step*0.01)-(calc22)*sin(step*0.01); while(x<0){x+=640;} while(x>639){x-=640;}
                    y=(calc32)*-sin(step*0.01)+(calc22)*cos(step*0.01); while(y<0){y+=480;} while(y>479){y-=480;}

                    bg->putPixel(i,j,bgImg[x][y]);
                }
            }
        }

        step++;
        deltacount = 0.0f;
    }

    if(16800 <= RF_Engine::instance->time->fixedCTime())
    {
        bg->clearSurface(0x000000);
        dynamic_cast<mainProcess*>(RF_Engine::instance->taskManager[father])->state() = 5;
    }
}
