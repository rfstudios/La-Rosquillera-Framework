#ifndef RF_PARALLAX_H
#define RF_PARALLAX_H

#include "rf_parallax_layer.h"
#include <vector>
using namespace std;

class RF_Parallax
{
    public:
        RF_Parallax(){}
        virtual ~RF_Parallax(){}

        void newLayer();

    private:
        vector<RF_Parallax_Layer*> layers;
};

#endif // RF_PARALLAX_H
