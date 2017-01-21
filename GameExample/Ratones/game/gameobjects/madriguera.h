#ifndef MADRIGUERA_H
#define MADRIGUERA_H

#include "rf_process.h"

class Madriguera : public RF_Process
{
    public:
        Madriguera(int spawnColor):RF_Process("Madriguera")
        {
            color = spawnColor;
        }
        virtual ~Madriguera(){}

        virtual void Start();
        virtual void Update();

        int& Color(){ return color;}

    private:
        int color;
};

#endif // MADRIGUERA_H
