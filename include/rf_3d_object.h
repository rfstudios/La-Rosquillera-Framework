#ifndef RF_3D_OBJECT_H
#define RF_3D_OBJECT_H

#include "rf_declares.h"

class RF_3D_Object
{
    public:
        RF_3D_Object(){};
        virtual ~RF_3D_Object(){};

        Transform3D transform;
        vector<Faces> faces;
        vector<Vector3<float>> vertex; //Lista de entrada de los vértices al ser cargados
                                    //Y lista de vértices tras calcular la rotación

        void finalizeCreation(){
            _vertex = vertex;
        }

        void calculateMesh();
    private:
        vector<Vector3<float>> _vertex; //Información original del objeto
};

#endif // RF_3D_OBJECT_H
