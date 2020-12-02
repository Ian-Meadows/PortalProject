#ifndef CAMERA_H
#define CAMERA_H

#include <GL/glut.h>
#include "Object.h"
#include <string>
#include <math.h>

#include "Def.h"
#include "SimpleObject.h"

class Camera{
public:
    Camera(Vector3D position, Vector3D rotation);
    Camera();
    ~Camera();

    void Draw();
    void UpdateProjection(double worldDimension, double aspectRatio, int width, int height);
    void UpdateProjection();

    void drawSelf();


    void KeyPressed(unsigned char k, int x, int y);
    void SpecialKeyPressed(int k, int x, int y);

    void Update(Vector3D position, Vector3D rotation);

    Vector3D GetPosition();
    Vector3D GetRotation();

    std::string GetProjectionType();


    Vector3D GetForward();
    Vector3D GetRight();
    Vector3D GetUp();

    int GetWidth() const { return width; }
    int GetHeight() const { return height; }
    double GetAspectRatio() const { return aspectRatio; }


private:

    void IncreaseProjectionType();
    void DecreaseProjectionType();

    void ResetView();

    int projectionType = 2;

    Vector3D position;
    Vector3D rotation;
    Vector3D viewDirection;

    int fov = 55;

    //current
    double worldDimension;
    double aspectRatio;
    int width;
    int height;

    //perspective and orthographic
    const Vector3D OVERHEAD_POS = Vector3D(0, 0, 0);
    const Vector3D OVERHEAD_ROT = Vector3D(300, 45, 0);


    //First Person
    const Vector3D FIRST_PERSON_POS = Vector3D(0.5, 2.5, 0.5);
    const Vector3D FIRST_PERSON_ROT = Vector3D(0, 270, 0);

};

#endif