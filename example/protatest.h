#ifndef PROTATEST_H
#define PROTATEST_H

#include "rf_sprite.h"


class protatest : public RF_Sprite
{
    public:
        protatest():RF_Sprite("Prota","lluvia",4,4,10){}
        virtual ~protatest(){}

        void Start()
        {
            ctype = C_SCROLL;
        }

        void Update()
        {
            if(RF_Engine::instance->key[_w])
            {
                transform.position.y -= speed;
                currentAnimation() = 2;
            }
            else if(RF_Engine::instance->key[_s])
            {
                transform.position.y += speed;
                currentAnimation() = 0;
            }

            if(RF_Engine::instance->key[_a])
            {
                transform.position.x -= speed;
                currentAnimation() = 1;
            }
            else if(RF_Engine::instance->key[_d])
            {
                transform.position.x += speed;
                currentAnimation() = 3;
            }

            zLayer = (int) transform.position.y;
            if(zLayer < 0){zLayer = 0;}
        }

        int speed = 25, orient = 0;
};

#endif // PROTATEST_H
