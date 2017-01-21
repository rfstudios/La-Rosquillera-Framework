#ifndef ENDSCENE_H
#define ENDSCENE_H

#include "rf_process.h""

class EndScene : public RF_Process
{
    public:
        EndScene():RF_Process("EndScene"){}
        virtual ~EndScene(){}
};

#endif // ENDSCENE_H
