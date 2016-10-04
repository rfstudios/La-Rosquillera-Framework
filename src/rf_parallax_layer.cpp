#include "rf_parallax_layer.h"
#include "rf_primitive.h"

RF_Parallax_Layer::RF_Parallax_Layer(string image_path, Vector2<float> speed)
{
    if(image_path == ""){size.x = -1; return;}
    lSpeed = speed;

    transform.position = Vector2<int>(0,0);
    transform.scale = Vector2<int>(1,1);
    transform.rotation=0;

    SDL_Surface* bgImgS = RF_Engine::instance->loadPNG_Surface(image_path);
    size.x = bgImgS->w; size.y = bgImgS->h;

    for(j=0; j<bgImgS->h; j++)
    {
        for(i=0; i<bgImgS->w; i++)
        {
            data.push_back(RF_Primitive::getPixel(bgImgS,i,j));
        }
    }
    SDL_FreeSurface(bgImgS);
}

Uint32 RF_Parallax_Layer::getRotoPixel(Vector2<int> pos)
{
    if(size.x == -1){return 0x000000;}

    tmp = RF_Engine::instance->rotozoom(pos, transform, size);
    i = size.x*tmp.y + tmp.x;

    return data[i];
}
