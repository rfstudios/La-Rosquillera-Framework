#ifndef MAINMENU_H
#define MAINMENU_H

#include "rf_process.h"

class OptButton : public RF_Process
{
    public:
        OptButton(string n):RF_Process(n){}
        ~OptButton(){}
};

class MainMenu : public RF_Process
{
    public:
        MainMenu():RF_Process("MainMenu"){}
        virtual ~MainMenu(){}

        virtual void Start();
        virtual void Update();

    private:
        OptButton *bt1, *bt2, *checked = NULL;
        Vector2<int> btscal1, btscal2;
};

#endif // MAINMENU_H
