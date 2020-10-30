#ifndef SIMPLE_OBJECT_H
#define SIMPLE_OBJECT_H

#include "Object.h"


class SimpleObject : public Object{
public:
    SimpleObject(Vector3D pos, Vector3D scale, Vector3D rotation);
    ~SimpleObject();
    
private:
    void DrawShape();

};

#endif