#ifndef LIGHT_H
#define LIGHT_H

#include "Object.h"
#include "Shader.h"

struct LightInfo{
    GLenum lightNumber;
    bool isSpotLight;

    Vector3D diffuse;
    Vector3D specular;

    Vector3D position;

    Vector3D lightObjectColor;

    LightInfo(){
        this->lightNumber = GL_LIGHT0;
        isSpotLight = false;
        diffuse = Vector3D(0.3);
        specular = Vector3D(0.3);

        position = Vector3D();
        lightObjectColor = Vector3D(1.0);
    }

    LightInfo(GLenum lightNumber){
        this->lightNumber = lightNumber;
        isSpotLight = false;
        diffuse = Vector3D(0.3);
        specular = Vector3D(0.3);

        position = Vector3D();
        lightObjectColor = Vector3D(1.0);
    }

    LightInfo(GLenum lightNumber, Vector3D position){
        this->lightNumber = lightNumber;
        isSpotLight = false;
        diffuse = Vector3D(0.3);
        specular = Vector3D(0.3);

        this->position = position;
        lightObjectColor = Vector3D(1.0);
    }

    LightInfo(GLenum lightNumber, Vector3D position,
     Vector3D diffuse, Vector3D specular){
        this->lightNumber = lightNumber;
        isSpotLight = false;
        this->diffuse = diffuse;
        this->specular = specular;

        this->position = position;
        lightObjectColor = Vector3D(1.0);
    }

    LightInfo(GLenum lightNumber, Vector3D position,
     Vector3D diffuse, Vector3D specular, Vector3D lightObjectColor){
        this->lightNumber = lightNumber;
        isSpotLight = false;
        this->diffuse = diffuse;
        this->specular = specular;

        this->position = position;
        this->lightObjectColor = lightObjectColor;
    }
};

class Light{
public:
    Light(LightInfo info);
    virtual ~Light();

    

    void Draw(Vector3D ambientLight, Shader* shader);


    Vector3D GetPosition()const {return li.position; }

protected:
    virtual void DrawShape();
    virtual void ChangePosition(int zh);

    void SetPosition(Vector3D position);

private:

    void Vertex(double th, double ph);

    void UpdatePosition();

    void UpdateLighting(Vector3D ambientLight);

    LightInfo li;

    int inc       =  10;  // Ball increment

};


#endif