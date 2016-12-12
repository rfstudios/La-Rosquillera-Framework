#include "rf_sprite.h"

void RF_Sprite::Draw()
{
    if(spriteset != "")
    {
        if(anim + frame == 0)
        {
            if(graph == NULL)
            {
                graph = RF_Engine::instance->getGfx2D(spriteset);
            }
        }
        else if(nextFrame)
        {
            graph = RF_Engine::instance->getGfx2D((spriteset + "_" + to_string(aFrame) + "_" + to_string(aAnim)));
            nextFrame = false;
        }
    }

    deltaCount += RF_Engine::instance->time->deltaTime;
    if(deltaCount >= (1 / speed))
    {
        deltaCount = 0.0f;
        aFrame++;
        if(aFrame >= frame)
        {
            aFrame = 0;
        }
        nextFrame = true;
    }
}
