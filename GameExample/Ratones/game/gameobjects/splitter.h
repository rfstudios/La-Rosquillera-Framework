#ifndef SPLITTER_H
#define SPLITTER_H

#include "rf_engine.h"
#include "gameobjects/dureza.h"
#include "game.h"

class Splitter : public Node
{
    public:
        Splitter():Node(){}
        virtual ~Splitter()
        {
            Game::instance->Plataformas[((int)split->transform.position.x)/10][((int)split->transform.position.y)/10] = 0;
        }

        virtual void Start()
        {
            graph = RF_Engine::instance->getGfx2D("splitter");
        }

        virtual void Update()
        {
            if(realPos.x == -1)
            {
                realPos.x = (int)transform.position.x;
                realPos.y = (int)transform.position.y;

                int s = RF_Engine::instance->newTask(new dureza(),id);
                split = dynamic_cast<dureza*>(RF_Engine::instance->taskManager[s]);
                split->transform.position = transform.position;
                split->transform.position.x -= 10;
                split->transform.position.y -= 10;

                Game::instance->Plataformas[(realPos.x - 10)/10][(realPos.y - 10)/10] = 1;
                dir = true;
            }

            if(dir)
            {
                transform.position.x += 10;
                if(RF_Engine::instance->collision("NPC_Raton",this))
                {
                    dir = false;
                    Game::instance->Plataformas[(realPos.x + 10)/10][(realPos.y - 10)/10] = 1;
                    Game::instance->Plataformas[(realPos.x - 10)/10][(realPos.y - 10)/10] = 0;

                    split->transform.position.x = realPos.x + 10;
                }
            }
            else
            {
                transform.position.x -= 10;
                if(RF_Engine::instance->collision("NPC_Raton",this))
                {
                    dir = true;
                    Game::instance->Plataformas[(realPos.x + 10)/10][(realPos.y - 10)/10] = 0;
                    Game::instance->Plataformas[(realPos.x - 10)/10][(realPos.y - 10)/10] = 1;

                    split->transform.position.x = realPos.x-10;
                }
            }

            transform.position.x = realPos.x;
        }

    private:
        bool dir = false;
        dureza* split = NULL;

        Vector2<int> realPos = Vector2<int>(-1,0);
};

#endif // SPLITTER_H
