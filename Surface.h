#pragma once
#include "Object.h"

class Surface : public Object
{
public:
    Surface(Vector3D pos, Vector3D scale, Vector3D rotation);
    bool portalable();

private:
    void DrawShape();
};