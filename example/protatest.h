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
            ctype = C_SCROLL;
        }

        void Update()
        {
            deltaPlus += RF_Engine::instance->time->deltaTime;
            if(deltaPlus > 0.25f)
            {
                deltaPlus = 0.0f;

                frame++;
                if(frame > 3){frame = 0;}
            }

            if(RF_Engine::instance->key[_w])
            {
                transform.position.y -= speed;
                orient = 2;
            }
            else if(RF_Engine::instance->key[_s])
            {
                transform.position.y += speed;
                orient = 0;
            }

            if(RF_Engine::instance->key[_a])
            {
                transform.position.x -= speed;
                orient = 1;
            }
            else if(RF_Engine::instance->key[_d])
            {
                transform.position.x += speed;
                orient = 3;
            }
                graph = RF_Engine::instance->getGfx2D(("lluvia_" + to_string(frame) + "_" + to_string(orient)));
        }

        int speed = 25, frame = 0, orient = 0;
        float deltaPlus = 0.0f;
};

#endif // PROTATEST_H
