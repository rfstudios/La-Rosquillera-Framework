#ifndef RF_PARALLAX_LAYER_H
#define RF_PARALLAX_LAYER_H

#include "rf_engine.h"
#include "rf_declares.h"
#include <SDL/SDL_image.h>

class RF_Parallax_Layer
{
    public:
        RF_Parallax_Layer(string image_path="");
        virtual ~RF_Parallax_Layer(){}

        Uint32 getRotoPixel(Vector2<int> pos);

        vector<Uint32> data;
        Vector2<int> size;
        Transform2D<int> t;
    protected:
    private:
};

#endif // RF_PARALLAX_LAYER_H
