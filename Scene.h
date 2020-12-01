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
#include "Shader.h"
#include "Portal.h"
#include "Camera.h"
#include "Dropper.h"
#include "LightHandler.h"
#include "Wall.h"
#include "Floor.h"
#include "Observe.h"

namespace Scene
{
    void Init(Camera *camera);
    void Init(Vector3D size, Camera *camera);
    void CleanUp();

    void renderPortals(Camera *camera, int rec);
    void Draw(Camera *camera);

    void DrawShadowableObjects();

    void refreshScene();
    void setPortalsLocation(int pos);

        void SetSceneSize(Vector3D size);
    Vector3D GetSceneSize();
} // namespace Scene

#endif