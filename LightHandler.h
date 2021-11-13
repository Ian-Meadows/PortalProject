#ifndef LIGHT_HANDLER_H
#define LIGHT_HANDLER_H
#define GL_GLEXT_PROTOTYPES

#include "includes.h"


#include "Light.h"
#include "vector"
#include "Shader.h"
#include "Window.h"
#include "MovingLight.h"







namespace LightHandler{

    void Init(Shader* shader, Vector3D ambientLight, Camera* camera);


    void Update(bool isLighting);

    void AddLight(LightInfo lightInfo);
    void AddMovingLight(LightInfo lightInfo);


    void CleanUp();

}


#endif