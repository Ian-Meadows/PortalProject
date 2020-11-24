#ifndef LIGHT_HANDLER_H
#define LIGHT_HANDLER_H
#define GL_GLEXT_PROTOTYPES
#include <GL/glut.h>


#include "Light.h"
#include "vector"
#include "Shader.h"
#include "Window.h"







namespace LightHandler{

    void Init(Shader* shader);


    void Update(bool isLighting);

    /**
     * @param number is the light number for openGl to use
     * 
     */
    void AddLight(LightInfo info);


    void CleanUp();

}


#endif