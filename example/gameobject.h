#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <rf_sprite.h>

class gameobject : public RF_Sprite
{
    public:
        gameobject():RF_Sprite("Gameobject","mago",4,4,4.0f){}
        virtual ~gameobject(){}

        virtual void Start()
        {
            //graph = RF_Engine::instance->getGfx2D("euria");
            transform.position = Vector2<float>(1000,400);
            zLayer = (int) transform.position.y;
            ctype = C_SCROLL;
        }
};

#endif // GAMEOBJECT_H
