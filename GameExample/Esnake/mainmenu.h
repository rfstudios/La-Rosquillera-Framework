#ifndef MAINMENU_H
#define MAINMENU_H

#include "rf_background.h"
#include "rf_process.h"
#include "rf_engine.h"
#include "rf_parallax_layer.h"

#include <vector>
using namespace std;

class MainMenu : public RF_Process
{
    public:
        MainMenu():RF_Process("MainMenu"){}
        virtual ~MainMenu(){}

        virtual void Start();
        virtual void Update();

    private:
        RF_Parallax_Layer* pL;
        RF_Background* bg;

        int texto;
};

#endif // MAINMENU_H
