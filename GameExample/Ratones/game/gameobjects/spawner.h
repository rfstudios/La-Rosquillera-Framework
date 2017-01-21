#ifndef SPAWNER_H
#define SPAWNER_H

#include "rf_process.h"
#include "rf_engine.h"

class Spawner : public RF_Process
{
    public:
        Spawner(int spawnColor = SPAWN_RED, float frequency = 1.0):RF_Process("Spawner")
        {
            color = spawnColor;
            freq = frequency;
        }

        virtual ~Spawner(){}

        virtual void Start();
        virtual void Update();

        int& Color(){ return color;}
        float& Freq(){ return freq;}

    private:
        int color;
        float freq;
        float deltaCount = 0.0;

};

#endif // SPAWNER_H
