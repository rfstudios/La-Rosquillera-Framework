#ifndef RF_MATH_H
#define RF_MATH_H

#include <vector>
#include <math.h>
using namespace std;

class RF_Math
{
    public:
        RF_Math() { prepare();}
        virtual ~RF_Math() {}

        void prepare()
        {
            for(float i = 0.0f; i < 6.283f; i+=0.001f)
            {
                precCos.push_back(cos(i));
                precSin.push_back(sin(i));
            }
        }

        float preCos(int value)
        {
            //Explicación: ((Milésimas de grado) convertidas a grados) convertidos a radianes
                float val = ((value%360000)/1000.0f)*M_PI/180;
                return precCos[(int)(val*1000)];
        }

        float preSin(int value)
        {
            //Explicación: ((Milésimas de grado) convertidas a grados) convertidos a radianes
                float val = ((value%360000)/1000.0f)*M_PI/180;
                return precSin[(int)(val*1000)];
        }

    private:
        vector<float> precSin;
        vector<float> precCos;
};

#endif // RF_MATH_H
