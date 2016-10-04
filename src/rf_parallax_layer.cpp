#include "rf_parallax_layer.h"
#include "rf_primitive.h"

RF_Parallax_Layer::RF_Parallax_Layer(string image_path)
{
    SDL_Surface* bgImgS = RF_Engine::instance->loadPNG_Surface("resources/gfx/logo.png");
    size.x = bgImgS->w; size.y = bgImgS->h;

    for(int j=0; j<bgImgS->h; j++)
    {
        for(int i=0; i<bgImgS->w; i++)
        {
            data.push_back(RF_Primitive::getPixel(bgImgS,i,j));
        }
    }
    SDL_FreeSurface(bgImgS);
}

Uint32 RF_Parallax_Layer::getRotoPixel(Vector2<int> pos)
{
    Vector2<int> tmp = RF_Engine::instance->rotozoom(pos, t);
    int p = size.x*tmp.y + tmp.x;

    return data[p];
}
