#ifndef LIGHT_H
#define LIGHT_H

#include "Object.h"

struct LightInfo{
    GLenum lightNumber;
    bool isSpotLight;

    Vector3D diffuse;
    Vector3D specular;

    Vector3D position;

    LightInfo(){
        this->lightNumber = GL_LIGHT0;
        isSpotLight = false;
        diffuse = Vector3D(0.3);
        specular = Vector3D(0.3);

        position = Vector3D();
    }

    LightInfo(GLenum lightNumber){
        this->lightNumber = lightNumber;
        isSpotLight = false;
        diffuse = Vector3D(0.3);
        specular = Vector3D(0.3);

        position = Vector3D();
    }

    LightInfo(GLenum lightNumber, Vector3D position){
        this->lightNumber = lightNumber;
        isSpotLight = false;
        diffuse = Vector3D(0.7);
        specular = Vector3D(0.7);

        this->position = position;
    }

    LightInfo(GLenum lightNumber, Vector3D position,
     Vector3D diffuse, Vector3D specular){
        this->lightNumber = lightNumber;
        isSpotLight = false;
        this->diffuse = diffuse;
        this->specular = specular;

        this->position = position;
    }
};

class Light{
public:
    Light(LightInfo info);
    ~Light();

    virtual void DrawShape();

    virtual void Draw(Vector3D ambientLight) final;


    Vector3D GetPosition()const {return li.position; }

protected:
    virtual void ChangePosition();

private:
    //void DrawShape();

    void Vertex(double th, double ph);

    void UpdatePosition();

    void UpdateLighting(Vector3D ambientLight);

    LightInfo li;

    int inc       =  10;  // Ball increment
    int distance = 3;

};


#endif