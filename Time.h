#ifndef TIME_H
#define TIME_H

#include <iostream>
#include <GL/glut.h>

namespace Time{
    double GetFPS();
    double GetDeltaTime();

    void Init(bool);

    void Update();
}

#endif