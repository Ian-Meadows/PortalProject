#ifndef SCENE_H
#define SCENE_H

#define GL_GLEXT_PROTOTYPES
#include <GL/glut.h>
#include <vector>

#include "Object.h"

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