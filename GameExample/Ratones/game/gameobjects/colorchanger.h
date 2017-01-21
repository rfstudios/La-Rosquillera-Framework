#ifndef COLORCHANGER_H
#define COLORCHANGER_H

#include "rf_engine.h"
#include "game.h"
#include "gameobjects/dureza.h"
#include "gameobjects/npc_mouse.h"

class ColorChanger : public Node
{
    public:
        ColorChanger():Node(){}
        virtual ~ColorChanger()
        {
            if(barrier[0]->transform.position.y != transform.position.y)
            {
                Game::instance->Plataformas[(int)barrier[0]->transform.position.x/10][(int)barrier[0]->transform.position.y/10] = 0;
            }
            if(barrier[1]->transform.position.y != transform.position.y)
            {
                Game::instance->Plataformas[(int)barrier[1]->transform.position.x/10][(int)barrier[1]->transform.position.y/10] = 0;
            }
            if(target)
            {
                if(target->Speed().x == 0)
                {
                    Restaura();
                }
            }
        }

        virtual void Start()
        {
            graph = RF_Engine::instance->getGfx2D("colorchanger");
        }

        virtual void Update()
        {
            if(realPos.x == -1)
            {
                realPos.x = (int)transform.position.x;
                realPos.y = (int)transform.position.y;

                int aux = RF_Engine::instance->newTask(new dureza(),id);
                barrier[0] = dynamic_cast<dureza*>(RF_Engine::instance->taskManager[aux]);
                barrier[0]->transform.position.x = transform.position.x - 10;
                barrier[0]->transform.position.y = transform.position.y;

                aux = RF_Engine::instance->newTask(new dureza(),id);
                barrier[1] = dynamic_cast<dureza*>(RF_Engine::instance->taskManager[aux]);
                barrier[1]->transform.position.x = transform.position.x + 10;
                barrier[1]->transform.position.y = transform.position.y;
            }

            if(on_use == 0)
            {
                if(graph == NULL)
                {
                    graph = RF_Engine::instance->getGfx2D("colorchanger");
                }

                transform.position.y += 10;

                RF_Process* aux = RF_Engine::instance->collision("NPC_Raton", this);
                if(aux != NULL)
                {
                    on_use = 1;
                    target = dynamic_cast<NPC_Mouse*>(aux);
                    targetSpeed = target->Speed();
                    target->Speed() = Vector2<float>(0.0,0.0);
                    target->transform.position = transform.position;
                }

                transform.position.y = realPos.y;
            }
            else if(on_use == 1)
            {
                if(barrier[0]->transform.position.y == transform.position.y)
                {
                    barrier[0]->transform.position.y += 10;
                    Game::instance->Plataformas[(int)barrier[0]->transform.position.x/10][(int)barrier[0]->transform.position.y/10] = 1;
                }
                if(barrier[1]->transform.position.y == transform.position.y)
                {
                    barrier[1]->transform.position.y += 10;
                    Game::instance->Plataformas[(int)barrier[1]->transform.position.x/10][(int)barrier[1]->transform.position.y/10] = 1;
                }

                changing += RF_Engine::instance->time->deltaTime;

                if(changing >= 3.0)
                {
                    changing = 0.0;

                    Game::instance->population[target->Color()]--;
                    Restaura();
                    target->Color()++;
                    if(target->Color() > SPAWN_BLUE){target->Color() = SPAWN_RED;}
                    target->graph = RF_Engine::instance->getGfx2D(("mouse_" + to_string(target->Color())));
                    Game::instance->population[target->Color()]++;

                    graph = NULL;
                    on_use = 2;
                }
            }
            else
            {
                if(barrier[0]->transform.position.y != transform.position.y)
                {
                    Game::instance->Plataformas[(int)barrier[0]->transform.position.x/10][(int)barrier[0]->transform.position.y/10] = 0;
                    barrier[0]->transform.position.y = transform.position.y;
                }
                if(barrier[1]->transform.position.y != transform.position.y)
                {
                    Game::instance->Plataformas[(int)barrier[1]->transform.position.x/10][(int)barrier[1]->transform.position.y/10] = 0;
                    barrier[1]->transform.position.y = transform.position.y;
                }

                changing += RF_Engine::instance->time->deltaTime;

                if(changing >= 3.0)
                {
                    changing = 0.0;
                    on_use = 0;
                }
            }
        }

        void Restaura()
        {
            target->Speed() = targetSpeed;
            target->on_place = true;
        }

    private:
        int on_use = 0;
        float changing = 0.0;
        Vector2<int> realPos = Vector2<int>(-1,0);

        NPC_Mouse* target;
        Vector2<float> targetSpeed;

        dureza* barrier[2];
};

#endif // COLORCHANGER_H
