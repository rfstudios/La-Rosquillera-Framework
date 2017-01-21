#ifndef RATON_H
#define RATON_H

#include "rf_process.h"
#include "rf_engine.h"

class Raton : public RF_Process
{
    public:
        static Raton* instance;
        Raton():RF_Process("Raton")
        {
            instance = this;

            graph = RF_Engine::instance->getGfx2D("mouse");
        }
        virtual ~Raton(){}

        virtual void Start(){zLayer = 1000;}
        virtual void Update();

        bool collision(RF_Process* p);
        bool OnClick = false;
};

class Ingame_Mouse : public Raton
{
    public:
        Ingame_Mouse():Raton(){}
        virtual void Start()
        {
            graph = RF_Engine::instance->getGfx2D("mouse2");
            zLayer = 1000;
        }

        virtual void Update();
};

#endif // RATON_H
