#ifndef RF_PARALLAX_LAYER_H
#define RF_PARALLAX_LAYER_H

#include "rf_engine.h"
#include "rf_declares.h"
#include "rf_background.h"
#include <SDL2/SDL_image.h>

class RF_Parallax_Layer
{
    public:
        RF_Parallax_Layer(string file="", Vector2<float> speed = Vector2<float>(1.0f,1.0f), Vector2<bool> mirror = Vector2<bool>(true,false));
        virtual ~RF_Parallax_Layer(){}

        Uint32 getRotoPixel(Vector2<int> pos);

        vector<Uint32> data;
        Vector2<int> size;
        Transform2D<int> transform;

        Vector2<float>& getSpeed(){return lSpeed;}
        Vector2<bool>& getMirroring(){return _mirror;}
        int setGfx(string file);
        int setGfx(SDL_Surface* file);

        void drawAlone(RF_Background* bg);

    private:
        int i,j;
        Vector2<int> tmp;
        Vector2<bool> _mirror;
        Vector2<float> lSpeed;
};

#endif // RF_PARALLAX_LAYER_H
