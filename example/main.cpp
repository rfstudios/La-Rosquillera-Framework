/*ESTA ES UNA PRUEBA DE REPOSITORIOS*/

#include <SDL2/SDL.h>
#include "rf_declares.h"
#include "rf_engine.h"
#include "mainprocess.h"

int main()
{
    RF_Engine *e = new RF_Engine(false);
    e->newWindow("3D Ampliation", /*SDL_WINDOW_FULLSCREEN |*/ SDL_WINDOW_OPENGL, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_RENDERER_ACCELERATED);
    e->newTask(new mainProcess());

    do
    {
        e->run();
        SDL_Delay(1);
    }while(e->isRunning());

    e->destroyWindow();

    return 0;
}

