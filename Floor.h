#ifndef FLOOR_H
#define FLOOR_H


#include "Object.h"


class Floor : public Object{
public:
    Floor(Vector3D pos, Vector3D scale, Vector3D rotation);
    ~Floor();


private:
    void DrawShape();


};


#endif