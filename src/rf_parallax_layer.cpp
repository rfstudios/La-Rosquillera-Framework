#include "rf_parallax_layer.h"
#include "rf_primitive.h"

RF_Parallax_Layer::RF_Parallax_Layer(string file, Vector2<float> speed, Vector2<int> mirror){
    lSpeed = speed;
    _mirror = mirror;

    if(file == ""){size.x = -1; return;}
    int error = setGfx(file);
}
RF_Parallax_Layer::RF_Parallax_Layer(SDL_Surface* srf, Vector2<float> speed, Vector2<int> mirror){
    lSpeed = speed;
    _mirror = mirror;

    if(srf == NULL){size.x = -1; return;}
    int error = setGfx(srf);
}

void RF_Parallax_Layer::setPos(Vector2<int> newPos){
    transform.position.x = newPos.x;
    transform.position.y = newPos.y;

    if((transform.position.x < 0 || transform.position.x + RF_Engine::instance->ventana->width() > size.x) && _mirror.x == BLOCK)
    {
        if(transform.position.x < 0) transform.position.x = 0;
        else transform.position.x = size.x - RF_Engine::instance->ventana->width();
    }

    if((transform.position.y < 0 || transform.position.y + RF_Engine::instance->ventana->height() > size.y) && _mirror.y == BLOCK)
    {
        if(transform.position.y < 0) transform.position.y = 0;
        else transform.position.y = size.y - RF_Engine::instance->ventana->height();
    }
}

int RF_Parallax_Layer::setGfx(string file){
    return setGfx(RF_Engine::instance->getGfx2DSrf(file));
}
int RF_Parallax_Layer::setGfx(SDL_Surface* file){
    transform.position = Vector2<int>(0,0);
    transform.scale = Vector2<float>(1.0f,1.0f);
    transform.rotation=0;

    file;
    size.x = file->w; size.y = file->h;

    for(j=0; j<file->h; j++)
    {
        for(i=0; i<file->w; i++)
        {
            data.push_back(RF_Primitive::getPixel(file,i,j));
        }
    }

    return 0;
}

Uint32 RF_Parallax_Layer::getRotoPixel(Vector2<int> pos){
    if(size.x == -1){return 0x000000;}

    tmp = RF_Engine::instance->rotozoom(pos, transform, size, Vector2<bool>(_mirror.x == REPEAT, _mirror.y == REPEAT));
    return data[size.x*tmp.y + tmp.x];
}

void RF_Parallax_Layer::drawAlone(){
    for(j = RF_Background::instance->screen->h - 1; j >= 0; j--)
    {
        for(i = RF_Background::instance->screen->w - 1; i >= 0; i--)
        {
            RF_Background::instance->putPixel(i,j,getRotoPixel(Vector2<int>(i,j)));
        }
    }
}
