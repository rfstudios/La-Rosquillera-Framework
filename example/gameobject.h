#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <rf_process.h>

class gameobject : public RF_Process
{
    public:
        gameobject() : RF_Process("Gameobject"){}
        virtual ~gameobject(){}

        virtual void Start()
        {
            graph = RF_Engine::instance->getGfx2D("euria");
            transform.position = Vector2<float>(1000,400);
            ctype = C_SCROLL;
        }
};

#endif // GAMEOBJECT_H
