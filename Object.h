#ifndef OBJECT_H
#define OBJECT_H


#include <iostream>
#define GL_GLEXT_PROTOTYPES
#include <GL/glut.h>
#include <math.h>
#include <vector>

#include "TextureHandler.h"

//taken from CSCIx229.h
#define Cos(th) cos(3.1415926/180*(th))
#define Sin(th) sin(3.1415926/180*(th))

struct Vector3D{
    double x, y, z;

    Vector3D(){
        x = 0.0;
        y = 0.0;
        z = 0.0;
    }

    Vector3D(double n){
        x = n;
        y = n;
        z = n;
    }

    Vector3D(double x, double y, double z){
        this->x = x;
        this->y = y;
        this->z = z;
    }

    Vector3D Clone(){
        return Vector3D(x, y, z);
    }

    void Update(double x, double y, double z){
        this->x = x;
        this->y = y;
        this->z = z;
    }

    bool operator==(Vector3D const &other){
        if(other.x == x && other.y == y && other.z == z){
            return true;
        }
        else{
            return false;
        }
    }

    Vector3D Add(Vector3D other){
        return Vector3D(x + other.x, y + other.y, z + other.z);
    }
    Vector3D Subtract(Vector3D other){
        return Vector3D(x - other.x, y - other.y, z - other.z);
    }


    Vector3D Normalize(){
        double length = sqrt((x*x) + (y*y) + (z*z));
        Vector3D normalized(x / length, y / length, z / length);

        return normalized;
    }

    Vector3D Cross(Vector3D other){
        Vector3D cross((y*other.z) - (z*other.y),
             (z*other.x) - (x*other.z),
             (x * other.y) - (y * other.x));

        return cross;
    }

    Vector3D operator+(Vector3D const &other){
        Vector3D vec(x + other.x, y + other.y, z + other.z);
        return vec;
    }

    void Print(){
        std::cout << "x: " << x << " y: "<< y << " z: " << z << std::endl;
    }
    void Print(std::string message){
        std::cout << message << ": " << x << ", "<< y << ", " << z << std::endl;
    }


};


class Object{

public:
    Object(Vector3D pos, Vector3D scale, Vector3D rotation);
    virtual ~Object();
    virtual void Draw() final;

protected:
    Vector3D position;
    Vector3D scale;
    Vector3D rotation;


    virtual void DrawShape();

    virtual void LoadTextures(std::vector<std::string> textureFiles, std::vector<bool> hasAlpha) final;

    unsigned int* textures = nullptr;

private:


};

#endif