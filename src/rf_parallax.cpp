#include "rf_parallax.h"

RF_Parallax::RF_Parallax(Vector2<int> position):RF_Process("RF_Parallax")
{
    RF_Engine::instance->newTask(this,-1);
    transform.position = position;
}
RF_Parallax::RF_Parallax(int x, int y):RF_Process("RF_Parallax")
{
    RF_Engine::instance->newTask(this,-1);
    transform.position.x = x;
    transform.position.y = y;
}

void RF_Parallax::draw(RF_Background* bg)
{
    for(i = bg->screen->w - 1; i >= 0; i--)
    {
        for(j = bg->screen->h - 1; j >= 0; j--)
        {
            color = 0x000000;
            for(ii = 0; ii < layers.size() && color == 0x000000; ii++)
            {
                color = layers[ii]->getRotoPixel(Vector2<int>(i,j));
            }

            bg->putPixel(i,j,color);
        }
    }
}

int RF_Parallax::newLayer(string path, Vector2<float> speed, Vector2<int> mirror)
{
    layers.push_back(new RF_Parallax_Layer(path,speed,mirror));

    if(size.x < layers[layers.size()-1]->size.x){size.x = layers[layers.size()-1]->size.x;}
    if(size.y < layers[layers.size()-1]->size.y){size.y = layers[layers.size()-1]->size.y;}

    return layers.size();
}

int RF_Parallax::newLayer(SDL_Surface* srf, Vector2<float> speed, Vector2<int> mirror)
{
    layers.push_back(new RF_Parallax_Layer(srf,speed,mirror));

    if(size.x < layers[layers.size()-1]->size.x){size.x = layers[layers.size()-1]->size.x;}
    if(size.y < layers[layers.size()-1]->size.y){size.y = layers[layers.size()-1]->size.y;}

    return layers.size();
}

void RF_Parallax::move(Vector2<int> newPosition)
{
    move(newPosition.x,newPosition.y);
}

void RF_Parallax::move(int x, int y)
{
    transform.position.x += x;
    transform.position.y += y;

    for(ii = 0; ii < layers.size(); ii++)
    {
        layers[ii]->setPos(
            Vector2<int>(layers[ii]->transform.position.x + (float)x / layers[ii]->getSpeed().x,
                         layers[ii]->transform.position.y + (float)y / layers[ii]->getSpeed().y)
        );
    }
    needDraw = true;
}

void RF_Parallax::position(Vector2<int> newPosition)
{
    position(newPosition.x,newPosition.y);
}

void RF_Parallax::position(int x, int y)
{
    transform.position.x = x;
    transform.position.y = y;

    for(ii = 0; ii < layers.size(); ii++)
    {
        layers[ii]->setPos(
            Vector2<int>((float)x / layers[ii]->getSpeed().x,
                         (float)y / layers[ii]->getSpeed().y)
        );
    }

    needDraw = true;
}

void RF_Parallax::Draw()
{
    if(needDraw)
    {
        draw(RF_Background::instance);
        needDraw = false;
    }
}

RF_Scroll* RF_Scroll::instance = NULL;

void RF_Scroll::setCamera(int _target)
{
    target = RF_Engine::instance->taskManager[_target];
}

void RF_Scroll::Update()
{
    if(target != NULL)
    {
        Vector2<int> newPos = transform.position;
        if(target->transform.position.x > RF_Engine::instance->ventana->width()>>1 && target->transform.position.x < size.x - (RF_Engine::instance->ventana->width()>>1))
        {
            newPos.x = target->transform.position.x - (RF_Engine::instance->ventana->width()>>1);
        }

        if(target->transform.position.y > RF_Engine::instance->ventana->height()>>1 && target->transform.position.y < size.y - (RF_Engine::instance->ventana->height()>>1))
        {
            newPos.y = target->transform.position.y - (RF_Engine::instance->ventana->height()>>1);
        }

        position(newPos);
    }
}
