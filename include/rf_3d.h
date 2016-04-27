#ifndef RF_3D_H
#define RF_3D_H

#include "rf_declares.h"
#include "rf_3d_object.h"
#include <vector>
using namespace std;

class RF_3D
{
    public:
        RF_3D(){}
        virtual ~RF_3D(){}

        static void Draw(){}
        static SDL_Surface* Draw_Only(int objID = 0);
        static int loadObj(string file);

        static int& renderMode(){return _renderMode;}

        static vector<RF_3D_Object*> objectList;
        static int _renderMode;
};

#endif // RF_3D_H
