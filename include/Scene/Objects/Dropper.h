#ifndef Dropper_h
#define Dropper_h

#include "Object.h"

class Dropper : public Object
{
private:
public:

    Dropper(Vector3D pos, Vector3D scale, Vector3D rotation);

    //borrowed from ex8 with slight edits

    void rotate(GLdouble x, GLdouble y, GLdouble z);

    //draws a cylinder with a given radius and height at the specified resolution
    void cylinder(GLint angleChange, GLdouble radius, GLdouble height);
    void bottomring(GLint angleChange, GLdouble innerradius, GLdouble outerradius);
    void topring(GLint angleChange, GLdouble innerradius, GLdouble outerradius);
    void gate(GLint angleChange, GLdouble radius);
    void rods(GLint count);

    void DrawShape() override;
    
};
#endif