#ifndef DUREZA_H
#define DUREZA_H

#include "rf_process.h"

class dureza : public Node
{
    public:
        dureza():Node(){}
        virtual ~dureza(){}

        virtual void Start()
        {
            graph = RF_Engine::instance->getGfx2D("plataforma");
            zLayer = 1;
        }
};

#endif // DUREZA_H
