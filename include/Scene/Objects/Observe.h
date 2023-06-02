#pragma once

#include "Object.h"

class Observe : public Object
{
private:
public:
    Observe(Vector3D pos, Vector3D scale, Vector3D rotation);

    void cylinder(GLint angleChange, GLdouble radius, GLdouble height);
    void cam(GLint angleChange, GLdouble radius, GLdouble height);

    void DrawShape();
};