#ifndef Companion_h
#define Companion_h

#include "Object.h"

class Companion : public Object
{
private:
public:

    Companion(Vector3D pos, Vector3D scale, Vector3D rotation);

    //borrowed from ex8 with slight edits
    void cube();

    void sidePanel();

    void cornerPanel();

    void rotate(GLdouble x, GLdouble y, GLdouble z);

    //draws a cylinder with a given radius and height at the specified resolution
    void cylinder(GLint angleChange, GLdouble radius, GLdouble height);

    void DrawShape();
};
#endif