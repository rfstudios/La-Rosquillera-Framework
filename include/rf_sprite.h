#ifndef RF_SPRITE_H
#define RF_SPRITE_H

#include <rf_process.h>
#include "rf_engine.h"
#include <string>
using namespace std;

class RF_Sprite : public RF_Process
{
    public:
        RF_Sprite(string _type, string gfx = "", int animations = 0, int frames = 0, float fps = 4.0f):RF_Process(_type)
        {
            anim = animations;
            frame = frames;
            spriteset = gfx;

            speed = fps;
        }

        virtual ~RF_Sprite(){}
        virtual void Draw();

        int getAnimationCount(){return anim;}
        int getFrameCount(){return frame;}
        string getSpritesetID(){return spriteset;}

        float& frameSpeed(){return speed;}
        int& currentAnimation(bool update = true){nextFrame = update; return aAnim;}
        int& currentFrame(bool update = true){nextFrame = update; return aFrame;}

        void setSpriteset(string gfx, int animations = 0, int frames = 0)
        {
            anim = animations;
            frame = frames;
            spriteset = gfx;
        }

        bool nextFrame = true;

    private:
        int aAnim = 0, aFrame = 0;
        int anim,frame;
        string spriteset;
        float speed, deltaCount = 0.0f;
};

#endif // RF_SPRITE_H
