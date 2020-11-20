#pragma once

#include <iostream>
#define GL_GLEXT_PROTOTYPES
#include <GL/glut.h>
#include <math.h>
#include <vector>

#define Cos(th) cos(3.1415926 / 180 * (th))
#define Sin(th) sin(3.1415926 / 180 * (th))

void circleVertex(GLdouble ang);
void ovalVertex(GLdouble ang, GLdouble width, GLdouble height);