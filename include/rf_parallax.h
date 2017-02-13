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
        RF_Parallax(Vector2<int> position);
        RF_Parallax(int x=0, int y=0);
        virtual ~RF_Parallax(){}

        virtual void Draw();

        void draw();
        int newLayer(string path = "", Vector2<float> speed = Vector2<float>(1.0f, 1.0f), Vector2<int> mirror = Vector2<int>(1,0));
        int newLayer(SDL_Surface* srf = NULL, Vector2<float> speed = Vector2<float>(1.0f, 1.0f), Vector2<int> mirror = Vector2<int>(1,0));
        void move(Vector2<int> newPosition);
        void move(int x, int y);
        void position(Vector2<int> newPosition);
        void position(int x, int y);

        Transform2D<int> transform;
        Vector2<int> size = Vector2<int>(0,0);

    protected:
        vector<RF_Parallax_Layer*> layers;

        int i,j;
        unsigned int ii;
        Uint32 color;

        bool needDraw = false;
};

class RF_Scroll : public RF_Parallax
{
    public:
        static RF_Scroll* instance;

        RF_Scroll(Vector2<int> position) : RF_Parallax(position)
        {
            instance = this;
            target = NULL;
        }
        RF_Scroll(int x=0, int y=0) : RF_Parallax(x,y)
        {
            instance = this;
            target = NULL;
        }
        virtual ~RF_Scroll(){}

        void setCamera(int target);
        virtual void Update();

    private:
        RF_Process* target;
};

#endif // RF_PARALLAX_H
