#ifndef PROTATEST_H
#define PROTATEST_H

#include "rf_process.h"


class protatest : public RF_Process
{
    public:
        protatest(){}
        virtual ~protatest(){}

        void Start()
        {
            graph = RF_Engine::instance->getGfx2D("euria");
            ctype = C_SCROLL;
        }

        void Update()
        {
            if(RF_Engine::instance->key[_w])
            {
                transform.position.y -= speed;
            }
            else if(RF_Engine::instance->key[_s])
            {
                transform.position.y += speed;
            }

            if(RF_Engine::instance->key[_a])
            {
                transform.position.x -= speed;
            }
            else if(RF_Engine::instance->key[_d])
            {
                transform.position.x += speed;
            }
        }

        int speed = 25;
};

#endif // PROTATEST_H
