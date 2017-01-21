#include "mainprocess.h"
#include "execontrol.h"
#include "raton.h"

#include "splashscreen.h"
#include "mainmenu.h"
#include "game.h"
#include "endscene.h"

#include "rf_declares.h"
#include "rf_primitive.h"
#include "rf_soundmanager.h"
#include <SDL2/SDL_ttf.h>

mainProcess::~mainProcess(){}

void mainProcess::Start()
{
    //Levantamos el proceso que detectará, durante toda la ejecución, si pulsamos
    //la tecla esc;
        RF_Engine::instance->newTask(new exeControl(),id);

    //Cargamos recursos
        RF_Engine::instance->loadAsset("resources/common");
        RF_Engine::instance->font = RF_Engine::instance->getFont("Coving01",25);

    stateMachine = 1;
    //scene = RF_Engine::instance->newTask(new SplashScreen(),id);
    return;
}

void mainProcess::Update(){
    switch(stateMachine)
    {
        case 1: //MenuOpciones
            if(!RF_Engine::instance->exists("Raton"))
            {
                RF_Engine::instance->newTask(new Raton(),id);
            }

            if("MainMenu" != RF_Engine::instance->taskManager[scene]->type)
            {
                RF_Engine::instance->sendSignal(scene, S_KILL_TREE);
                RF_Engine::instance->time->setFixedCTime();

                scene = RF_Engine::instance->newTask(new MainMenu(),id);
            }
            break;
        case 2: //Game
            if("Game" != RF_Engine::instance->taskManager[scene]->type)
            {
                if(RF_Engine::instance->exists("Raton"))
                {
                    RF_Engine::instance->sendSignal("Raton", S_KILL_TREE);
                    RF_Engine::instance->newTask(new Ingame_Mouse(),-1);
                }

                RF_Engine::instance->sendSignal(scene, S_KILL_TREE);

                RF_Engine::instance->time->setFixedCTime();
                scene = RF_Engine::instance->newTask(new Game(),id);

                RF_SoundManager::playSong(RF_Engine::instance->getAudioClip("music"),-1);
            }
            break;
        case 3: //EndScene
            if("EndScene" != RF_Engine::instance->taskManager[scene]->type)
            {
                if(RF_Engine::instance->exists("Raton"))
                {
                    RF_Engine::instance->sendSignal("Raton", S_KILL_TREE);
                }

                RF_Engine::instance->deleteText(-1);
                RF_Engine::instance->sendSignal(scene, S_KILL_TREE);
                scene = RF_Engine::instance->newTask(new EndScene(),id);
            }
            break;
        /*case 4: //Scene4
            if("Scene4" != RF_Engine::instance->taskManager[scene]->type)
            {
                RF_Engine::instance->sendSignal(scene, S_KILL_TREE);

                RF_Engine::instance->time->setFixedCTime();
                scene = RF_Engine::instance->newTask(new Scene4(),id);
            }
            break;
        case 5: //Scene5
            if("Scene5" != RF_Engine::instance->taskManager[scene]->type)
            {
                RF_Engine::instance->sendSignal(scene, S_KILL_TREE);

                RF_Engine::instance->time->setFixedCTime();
                scene = RF_Engine::instance->newTask(new Scene5(),id);
            }
            break;
        case 6: //Scene6
            if("Scene6" != RF_Engine::instance->taskManager[scene]->type)
            {
                RF_Engine::instance->sendSignal(scene, S_KILL_TREE);

                RF_Engine::instance->time->setFixedCTime();
                scene = RF_Engine::instance->newTask(new Scene6(),id);
            }
            break;
        case 7: //Fin
            RF_Engine::instance->sendSignal(scene, S_KILL_TREE);
            RF_Engine::instance->isRunning(false);

            stateMachine = -1;
            break;*/
    }
    return;
}
