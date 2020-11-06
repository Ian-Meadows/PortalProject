#ifndef SCENE_H
#define SCENE_H

#define GL_GLEXT_PROTOTYPES
#include <GL/glut.h>
#include <vector>

#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <math.h>

#include <fstream>
#include <sstream>
#include <iostream>

#include "SimpleObject.h"
#include "ComplexObject.h"
#include "companion.h"
#include "Light.h"
#include "WhiteFloor.h"
#include "BlackFloor.h"
#include "WhiteWall.h"
#include "BlackWall.h"
#include "Shader.h"

namespace Scene{
    void Init();
    void Init(Vector3D size);
    void CleanUp();


    void Draw();

    void SetSceneSize(Vector3D size);
    Vector3D GetSceneSize();
}

#endif