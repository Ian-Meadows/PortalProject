#ifndef TIME_H
#define TIME_H

#include <iostream>
#ifdef USEGLEW
#include <GL/glew.h>
#endif
#define GL_GLEXT_PROTOTYPES
#include <GLFW/glfw3.h>
#ifdef __APPLE__
#include <OpenGL/glu.h>
#include <OpenGL/gl.h>
#else
#include <GL/glu.h>
#include <GL/gl.h>
#endif

namespace Time{
    double GetFPS();
    double GetDeltaTime();

    void Init(bool);

    void Update();
}

#endif