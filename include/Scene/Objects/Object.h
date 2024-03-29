#ifndef OBJECT_H
#define OBJECT_H

#include <iostream>

#include "includes.h"
#include <math.h>
#include <vector>

#include "TextureHandler.h"
#include "Def.h"
#include "Shader.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

//taken from CSCIx229.h

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

    Vector3D Negate()
    {
        return Vector3D(-x, -y, -z);
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

    double getMagnitude()
    {
        return sqrt((x * x) + (y * y) + (z * z));
    }

    Vector3D Rotate(Vector3D rot)
    {
        Vector3D result;
        //x  y  z
        result.x = x;
        result.y = y;
        result.z = z;
        if (rot.x != 0)
        {
            result = result.RotateAround(Vector3D(1, 0, 0), rot.x);
        }
        if (rot.y != 0)
        {
            result = result.RotateAround(Vector3D(0, 1, 0), rot.y);
        }
        if (rot.z != 0)
        {
            result = result.RotateAround(Vector3D(0, 0, 1), rot.z);
        }
        return result;
    }

    Vector3D RotateAround(Vector3D pivot, double deg)
    {
        Vector3D dis(x, y, z);
        return dis * Cos(deg) + (pivot.Cross(dis)) * Sin(deg) + pivot * (pivot.Dot(dis) * (1 - Cos(deg)));
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
    void Draw(Shader* shader);

protected:
    Vector3D position;
    Vector3D scale;
    Vector3D rotation;

    Vector3D getPosition();
    Vector3D getScale();
    Vector3D getRotation();

    void UpdateRotation(Vector3D rotation);

    virtual void DrawShape() = 0;

    void LoadTextures(std::vector<std::string> textureFiles, std::vector<bool> hasAlpha, std::string normalMap);

    //fixes rotation to be between 0 and 360
    void FixRotation();

    unsigned int *textures = nullptr;

    unsigned int normalMap = 0;
    bool hasNormalMap = false;
};

#endif