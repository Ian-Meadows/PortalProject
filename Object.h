#ifndef OBJECT_H
#define OBJECT_H

#include <iostream>
#define GL_GLEXT_PROTOTYPES
#include <GL/glut.h>
#include <math.h>
#include <vector>

#include "TextureHandler.h"

//taken from CSCIx229.h
#define Cos(th) cos(3.1415926 / 180 * (th))
#define Sin(th) sin(3.1415926 / 180 * (th))

struct Vector3D
{
    double x, y, z;

    Vector3D()
    {
        x = 0.0;
        y = 0.0;
        z = 0.0;
    }

    Vector3D(double n)
    {
        x = n;
        y = n;
        z = n;
    }

    Vector3D(double x, double y, double z)
    {
        this->x = x;
        this->y = y;
        this->z = z;
    }

    Vector3D Clone()
    {
        return Vector3D(x, y, z);
    }

    void Update(double x, double y, double z)
    {
        this->x = x;
        this->y = y;
        this->z = z;
    }

    bool operator==(Vector3D const &other)
    {
        if (other.x == x && other.y == y && other.z == z)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    Vector3D Add(Vector3D other)
    {
        return Vector3D(x + other.x, y + other.y, z + other.z);
    }
    Vector3D Subtract(Vector3D other)
    {
        return Vector3D(x - other.x, y - other.y, z - other.z);
    }

    Vector3D Normalize()
    {
        double length = sqrt((x * x) + (y * y) + (z * z));
        Vector3D normalized(x / length, y / length, z / length);

        return normalized;
    }

    Vector3D Cross(Vector3D other)
    {
        Vector3D cross((y * other.z) - (z * other.y),
                       (z * other.x) - (x * other.z),
                       (x * other.y) - (y * other.x));

        return cross;
    }

    double Dot(Vector3D other)
    {
        return x * other.x + y * other.y + z * other.z;
    }

    Vector3D operator+(Vector3D const &other)
    {
        Vector3D vec(x + other.x, y + other.y, z + other.z);
        return vec;
    }

    Vector3D operator*(double const &other)
    {
        Vector3D vec(x * other, y * other, z * other);
        return vec;
    }

    //hopefully this math is right
    Vector3D Rotate(Vector3D rot)
    {
        Vector3D result;
        //x  y  z
        result.x = x;
        result.y = y;
        result.z = z;
        if (rot.x != 0)
        {
            result.x = result.x;
            result.y = result.y * Cos(rot.x) + result.z * -Sin(rot.x);
            result.z = result.y * Sin(rot.x) + result.z * Cos(rot.x);
        }
        if (rot.y != 0)
        {
            result.x = result.x * Cos(rot.y) + result.z * Sin(rot.y);
            result.y = result.y;
            result.z = result.x * -Sin(rot.y) + result.z * Cos(rot.y);
        }
        if (rot.z != 0)
        {
            result.x = result.x * Cos(rot.z) + result.y * -Sin(rot.z);
            result.y = result.x * Sin(rot.z) + result.y * Cos(rot.z);
            result.z = result.z;
        }
        return result;
    }

    void Print()
    {
        std::cout << "x: " << x << " y: " << y << " z: " << z << std::endl;
    }
    void Print(std::string message)
    {
        std::cout << message << ": " << x << ", " << y << ", " << z << std::endl;
    }
};

class Object
{

public:
    Object(Vector3D pos, Vector3D scale, Vector3D rotation);
    virtual ~Object();
    virtual void Draw() final;

protected:
    Vector3D position;
    Vector3D scale;
    Vector3D rotation;

    Vector3D getPosition();
    Vector3D getScale();
    Vector3D getRotation();

    virtual void DrawShape();

    virtual void LoadTextures(std::vector<std::string> textureFiles, std::vector<bool> hasAlpha) final;


    //fixes rotation to be between 0 and 360
    virtual void FixRotation() final;


    unsigned int *textures = nullptr;

private:
};

#endif