#include "Def.h"

void circleVertex(GLdouble ang)
{
   glNormal3f(0, 1, 0);
   glVertex3d(Cos(ang), 0, Sin(ang));
}

void ovalVertex(GLdouble ang, GLdouble width, GLdouble height)
{
   glNormal3f(0, 1, 0);
   glVertex3d(width * Cos(ang), height * Sin(ang), 0);
}