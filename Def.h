#pragma once

#include <iostream>
#define GL_GLEXT_PROTOTYPES
#include <GL/glut.h>
#include <math.h>
#include <vector>

#define Cos(th) cos(3.1415926 / 180 * (th))
#define Sin(th) sin(3.1415926 / 180 * (th))

void circleVertex(GLdouble ang);
void circleVertex(GLdouble ang, GLdouble height);
void circleVertex(GLdouble ang, GLdouble height, GLdouble rad);
void ovalVertex(GLdouble ang, GLdouble width, GLdouble height);
void cyliVertex(GLdouble ang, GLdouble height);
void cyliVertex(GLdouble ang, GLdouble height, GLdouble rad);
void cyliVertex(GLdouble ang, GLdouble height, GLdouble rad, bool invert);

void sphereVertex(double th,double ph);
void sphere(double x,double y,double z,double r);