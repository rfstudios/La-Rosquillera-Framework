#ifndef RF_PARALLAX_H
#define RF_PARALLAX_H

#include "rf_parallax_layer.h"
#include "rf_declares.h"
#include "rf_background.h"
#include <vector>
using namespace std;

class RF_Parallax
{
    public:
        RF_Parallax(Vector2<int> position);
        RF_Parallax(int x=0, int y=0);
        virtual ~RF_Parallax(){}

        void draw(RF_Background* bg);
        int newLayer(string path = "", Vector2<float> speed = Vector2<float>(1.0f, 1.0f), Vector2<bool> mirror = Vector2<bool>(true,false));
        void move(Vector2<int> newPosition);
        void move(int x, int y);
        void position(Vector2<int> newPosition);
        void position(int x, int y);

        Transform2D<int> transform;

    private:
        vector<RF_Parallax_Layer*> layers;

        int i,ii,j;
        Uint32 color;
};

#endif // RF_PARALLAX_H
