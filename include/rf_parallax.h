#ifndef RF_PARALLAX_H
#define RF_PARALLAX_H

#include "rf_parallax_layer.h"
#include "rf_declares.h"
#include "rf_background.h"
#include "rf_process.h";
#include <vector>
using namespace std;

class RF_Parallax : public RF_Process
{
    public:
        static RF_Parallax* instance;

        RF_Parallax(Vector2<int> position);
        RF_Parallax(int x=0, int y=0);
        virtual ~RF_Parallax(){}

        void draw(RF_Background* bg);
        int newLayer(string path = "", Vector2<float> speed = Vector2<float>(1.0f, 1.0f), Vector2<int> mirror = Vector2<int>(1,0));
        void move(Vector2<int> newPosition);
        void move(int x, int y);
        void position(Vector2<int> newPosition);
        void position(int x, int y);

        void setCamera(int target);
        virtual void Update();

        Transform2D<int> transform;
        Vector2<int> size = Vector2<int>(0,0);

    private:
        vector<RF_Parallax_Layer*> layers;

        int i,j;
        unsigned int ii;
        Uint32 color;

        RF_Process* target;
};

#endif // RF_PARALLAX_H
