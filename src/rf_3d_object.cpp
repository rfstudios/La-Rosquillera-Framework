#include "rf_3d_object.h"
#include "rf_engine.h"
#include <math.h>

void RF_3D_Object::calculateMesh()
{
    unsigned int siz = _vertex.size();
    for(unsigned int i=0;i<siz;i++)
    {
        vertex[i].x = _vertex[i].x * transform.scale.x;
        vertex[i].y = _vertex[i].y * transform.scale.y;
        vertex[i].z = _vertex[i].z * transform.scale.z;

        vertex[i].x = (cos(transform.rotation.z)*(vertex[i].x*cos(transform.rotation.y)+vertex[i].y*sin(transform.rotation.x)*sin(transform.rotation.y)+vertex[i].z*cos(transform.rotation.x)*sin(transform.rotation.y))-sin(transform.rotation.z)*(vertex[i].y*cos(transform.rotation.x)-vertex[i].z*sin(transform.rotation.x)));
        vertex[i].y = (sin(transform.rotation.z)*(vertex[i].x*cos(transform.rotation.y)+vertex[i].y*sin(transform.rotation.x)*sin(transform.rotation.y)+vertex[i].z*cos(transform.rotation.x)*sin(transform.rotation.y))+cos(transform.rotation.z)*(vertex[i].y*cos(transform.rotation.x)-vertex[i].z*sin(transform.rotation.x)));
        vertex[i].z = (-vertex[i].x*sin(transform.rotation.y)+vertex[i].y*sin(transform.rotation.x)*cos(transform.rotation.y)+vertex[i].z*cos(transform.rotation.x)*cos(transform.rotation.y));

        vertex[i].x += transform.position.x;
        vertex[i].y += transform.position.y;
        vertex[i].z += transform.position.z;
    }
}
