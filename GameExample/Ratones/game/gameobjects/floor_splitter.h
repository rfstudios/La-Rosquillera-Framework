#ifndef FLOOR_SPLITTER_H
#define FLOOR_SPLITTER_H

#include "game.h"
#include "rf_process.h"
#include "rf_engine.h"


class Floor_Splitter : public Node
{
    public:
        Floor_Splitter():Node(){}
        virtual ~Floor_Splitter() {}

        virtual void Start()
        {
            graph = RF_Engine::instance->getGfx2D("floor_splitter");
        }

        virtual void Update()
        {
            if(realPos.x == -1)
            {
                realPos.x = (int)transform.position.x;
                realPos.y = (int)transform.position.y;
            }

            if(on_use == 0)
            {
                if(up)
                {
                    transform.position.y -= 10;
                }
                else
                {
                    transform.position.y += 10;
                }

                graph = RF_Engine::instance->getGfx2D("floor_splitter");
                target = RF_Engine::instance->collision("NPC_Raton", this);
                if(target != NULL)
                {
                    on_use = 1;
                }

                transform.position.y = realPos.y;

                if(!up){graph = NULL;}
            }
            else if(on_use == 1)
            {
                if(up)
                {
                    transform.position.y -= 10;
                    RF_Process* aux = RF_Engine::instance->collision("NPC_Raton", this);
                    if(target != aux)
                    {
                        up = false;
                        Game::instance->Plataformas[(realPos.x)/10][(realPos.y)/10] = 0;
                        graph = NULL;

                        on_use = 0;
                        target =  NULL;
                    }
                }
                else
                {
                    transform.position.y += 10;
                    graph = RF_Engine::instance->getGfx2D("floor_splitter");
                    RF_Process* aux = RF_Engine::instance->collision("NPC_Raton", this);
                    if(target != aux)
                    {
                        up = true;
                        Game::instance->Plataformas[(realPos.x)/10][(realPos.y)/10] = 1;
                        graph = RF_Engine::instance->getGfx2D("floor_splitter");

                        on_use = 0;
                        target =  NULL;
                    }
                    else
                    {
                        graph = NULL;
                    }
                }

                transform.position.y = realPos.y;
            }
        }

    private:
        bool up = true;
        int on_use = 0;
        RF_Process* target;

        Vector2<int> realPos = Vector2<int>(-1,0);
};

#endif // FLOOR_SPLITTER_H
