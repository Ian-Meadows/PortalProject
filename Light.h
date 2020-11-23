#ifndef LIGHT_H
#define LIGHT_H

#include "Object.h"

struct LightInfo{
    GLenum lightNumber;
    bool isSpotLight;


    Vector3D ambient;
    Vector3D diffuse;
    Vector3D specular;

    Vector3D position;

    LightInfo(){
        this->lightNumber = GL_LIGHT0;
        isSpotLight = false;
        ambient = Vector3D(0.1);
        diffuse = Vector3D(0.3);
        specular = Vector3D(0.3);

        position = Vector3D();
    }

    LightInfo(GLenum lightNumber){
        this->lightNumber = lightNumber;
        isSpotLight = false;
        ambient = Vector3D(0.1);
        diffuse = Vector3D(0.3);
        specular = Vector3D(0.3);

        position = Vector3D();
    }

    LightInfo(GLenum lightNumber, Vector3D position){
        this->lightNumber = lightNumber;
        isSpotLight = false;
        ambient = Vector3D(0.1);
        diffuse = Vector3D(0.3);
        specular = Vector3D(0.3);

        this->position = position;
    }

    LightInfo(GLenum lightNumber, Vector3D position, Vector3D ambient,
     Vector3D diffuse, Vector3D specular){
        this->lightNumber = lightNumber;
        isSpotLight = false;
        this->ambient = ambient;
        this->diffuse = diffuse;
        this->specular = specular;

        this->position = position;
    }
};

class Light{
public:
    Light(LightInfo info);
    ~Light();

    void DrawShape();
private:
    //void DrawShape();

    void Vertex(double th, double ph);

    void UpdatePosition();

    void UpdateLighting();

    LightInfo li;

    int inc       =  10;  // Ball increment
    int distance = 3;

};


#endif