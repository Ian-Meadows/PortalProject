#pragma once
#include "Object.h"
#include "Camera.h"

#define PORTAL_WIDTH 1024
#define PORTAL_HEIGHT 1024

class Portal : public Object
{
public:
    Portal(Vector3D pos, Vector3D scale, Vector3D rotation);
    void setOtherPortal(Portal* other);
    void enablePortalDrawing(Vector3D &pos, Vector3D &rot, Vector3D &thispos, Vector3D &thisrot);
    void endPortalDrawing();
    void setCam(Camera* c);
    Camera* getCam();

    ~Portal();

private:
    void DrawShape();

    Camera* cam;
    Portal* otherPortal;
    unsigned int fbo, rbo, finalTex;
    unsigned long int* temptex;
};