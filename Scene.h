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

#include "SimpleObject.h"
#include "ComplexObject.h"
#include "Floor.h"
#include "Light.h"

class Scene{

public:
    Scene();
    Scene(Vector3D size);
    ~Scene();


    void Draw();

    void SetSceneSize(Vector3D size);
    Vector3D GetSceneSize();

private:
    void Draw3DGraph(double len);

    void InitScene();

    std::vector<Object*> objects;


    Vector3D size;
};

#endif