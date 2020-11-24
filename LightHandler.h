#ifndef LIGHT_HANDLER_H
#define LIGHT_HANDLER_H
#define GL_GLEXT_PROTOTYPES
#include <GL/glut.h>


#include "Light.h"
#include "vector"
#include "Shader.h"
#include "Window.h"







namespace LightHandler{

    void Init(Shader* shader, Vector3D ambientLight, Camera* camera);


    void Update(bool isLighting);

    void AddLight(LightInfo info);

    void UpdateShadowMap();


    void CleanUp();

}


#endif