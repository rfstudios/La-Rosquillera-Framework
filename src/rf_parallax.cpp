#include "rf_parallax.h"

RF_Parallax::RF_Parallax(Vector2<int> position)
{
    transform.position = position;
}
RF_Parallax::RF_Parallax(int x, int y)
{
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

int RF_Parallax::newLayer(string path, Vector2<float> speed)
{
    layers.push_back(new RF_Parallax_Layer(path,speed));
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

    for(i = 0; i < layers.size(); i++)
    {
        layers[i]->transform.position.x += (float)x / layers[i]->lSpeed.x;
        layers[i]->transform.position.y += (float)y / layers[i]->lSpeed.y;
    }
}

void RF_Parallax::position(Vector2<int> newPosition)
{
    position(newPosition.x,newPosition.y);
}

void RF_Parallax::position(int x, int y)
{
    transform.position.x = x;
    transform.position.y = y;

    for(i = 0; i < layers.size(); i++)
    {
        layers[i]->transform.position.x = (float)x / layers[i]->lSpeed.x;
        layers[i]->transform.position.y = (float)y / layers[i]->lSpeed.y;
    }
}
