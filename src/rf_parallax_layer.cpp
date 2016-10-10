#include "rf_parallax_layer.h"
#include "rf_primitive.h"

RF_Parallax_Layer::RF_Parallax_Layer(string image_path, Vector2<float> speed, Vector2<bool> mirror)
{
    if(image_path == ""){size.x = -1; return;}
    lSpeed = speed;
    _mirror = mirror;

    transform.position = Vector2<int>(0,0);
    transform.scale = Vector2<float>(1.0f,1.0f);
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

    tmp = RF_Engine::instance->rotozoom(pos, transform, size, _mirror);
    return data[size.x*tmp.y + tmp.x];
}

void RF_Parallax_Layer::drawAlone(RF_Background* bg)
{
    for(i = bg->screen->w - 1; i >= 0; i--)
    {
        for(j = bg->screen->h - 1; j >= 0; j--)
        {
            bg->putPixel(i,j,getRotoPixel(Vector2<int>(i,j)));
        }
    }
}
