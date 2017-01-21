#ifndef EXECONTROL_H
#define EXECONTROL_H

#include "rf_process.h"

class exeControl : public RF_Process
{
    public:
        exeControl():RF_Process("exeProcess"){}
        virtual ~exeControl();

        virtual void Update();
    protected:
    private:
};

#endif // EXECONTROL_H
