#ifndef SPAWNER_H
#define SPAWNER_H

#include "rf_process.h"
#include "rf_engine.h"

class Spawner : public RF_Process
{
    public:
        Spawner(int spawnColor = SPAWN_RED, float frequency = 1.0):RF_Process("Spawner")
        {
            if(spawnColor > -1)
            {
                color = spawnColor;
            }
            else
            {
                color = rand()%4;
                change = true;

            }
            freq = frequency;
        }

        virtual ~Spawner(){}

        virtual void Start();
        virtual void Update();

        int& Color(){ return color;}
        float& Freq(){ return freq;}
        bool& Change(){ return change;}

        bool colors_to_change[4] = {true, true, true, true};

    private:
        int color;
        float freq;
        float deltaCount = 0.0;
        bool change = false;

};

#endif // SPAWNER_H
