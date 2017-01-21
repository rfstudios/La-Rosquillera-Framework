#ifndef ELEVATOR_H
#define ELEVATOR_H

#include "rf_process.h"
#include "rf_engine.h"
#include "gameobjects/npc_mouse.h"
#include "gameobjects/dureza.h"

class Elevator : public Node
{
    public:
        Elevator():Node(){}
        virtual ~Elevator()
        {
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
            graph = RF_Engine::instance->getGfx2D("elevator");
        }

        virtual void Update()
        {
            if(realPos.x == -1)
            {
                realPos.x = (int)transform.position.x;
                realPos.y = (int)transform.position.y;
                int aux = RF_Engine::instance->newTask(new dureza(),id);
                RF_Engine::instance->taskManager[aux]->transform.position = transform.position;
            }

            if(on_use == 0)
            {
                transform.position.y -= 10;

                RF_Process* aux = RF_Engine::instance->collision("NPC_Raton", this);
                if(aux != NULL)
                {
                    target = dynamic_cast<NPC_Mouse*>(aux);

                    if(target->Speed().x > 0.0)
                    {
                        targetSpeed = target->Speed();
                        target->Speed() = Vector2<float>(0.0,0.0);
                        target->transform.position = transform.position;
                        on_use = 1;
                    }
                }

                transform.position.y = realPos.y;
            }
            else if(on_use == 1)
            {
                if(((int)transform.position.y % 10) == 0 && Game::instance->Plataformas[(int)transform.position.x/10][(int)transform.position.y/10] > 0 && (int)transform.position.y != realPos.y)
                {
                    on_use = 2;
                    Restaura();
                }
                else
                {
                    transform.position.y--;
                    target->transform.position.y--;
                }
            }
            else
            {
                if((int)transform.position.y < realPos.y)
                {
                    transform.position.y += 0.2;
                }
                else
                {
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
        Vector2<int> realPos = Vector2<int>(-1,0);

        NPC_Mouse* target;
        Vector2<float> targetSpeed;
};

#endif // ELEVATOR_H
