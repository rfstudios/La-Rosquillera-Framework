#ifndef NPC_MOUSE_H
#define NPC_MOUSE_H

#include "rf_process.h"

enum DIRECTIONS{
    DIR_LEFT,
    DIR_RIGHT
};

class NPC_Mouse : public RF_Process
{
    public:
        NPC_Mouse(int spawnColor):RF_Process("NPC_Raton")
        {
            color = spawnColor;
        }
        virtual ~NPC_Mouse(){}

        virtual void Start();
        virtual void Update();

        int& Color(){ return color;}
        Vector2<float>& Speed(){ return speed;}
        bool on_place = false;

    private:
        int color;
        Vector2<float> speed = Vector2<float>(1.0, 0.5);
        int direction = DIR_RIGHT;
};

#endif // NPC_MOUSE_H
