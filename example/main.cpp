/*ESTA ES UNA PRUEBA DE REPOSITORIOS*/

#include <SDL2/SDL.h>
#include "rf_declares.h"
#include "rf_engine.h"
#include "mainprocess.h"

int main()
{
    //Creamos una instancia del motor
        RF_Engine *e = new RF_Engine(true);

    //Creamos una nueva ventana para el motor
        e->newWindow("Parallax", /*SDL_WINDOW_FULLSCREEN |*/ SDL_WINDOW_OPENGL, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_RENDERER_ACCELERATED);

    //Levantamos el proceso maestro de nuestro programa
        e->newTask(new mainProcess());

    do
    {
        e->run(); //Actualizamos el motor una iteración
        SDL_Delay(1); //Esperamos la mínima unidad posible (es vital para que SDL tome nuevos valores en I/O
    }while(e->isRunning()); //Repetimos mientras el motor esté encendido

    //Destruímos la ventana
        e->destroyWindow();

    return 0;
}

