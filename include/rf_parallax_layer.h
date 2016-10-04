#ifndef RF_PARALLAX_LAYER_H
#define RF_PARALLAX_LAYER_H

#include "rf_declares.h"
#include <SDL/SDL_image.h>

class RF_Parallax_Layer
{
    public:
        RF_Parallax_Layer(){}
        virtual ~RF_Parallax_Layer(){}

        Uint32 getRotoPixel(Vector2<int> pos);
    protected:
    private:
};

#endif // RF_PARALLAX_LAYER_H
