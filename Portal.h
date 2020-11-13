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
    Portal* getOtherPortal();
    void enablePortalDrawing(Vector3D &pos, Vector3D &rot, Vector3D &thispos, Vector3D &thisrot);
    void endPortalDrawing();
    void setCam(Camera* c);
    Camera* getCam();
    void setSurface(Object* s);
    Object* getSurface();

    ~Portal();

private:
    void DrawShape();

    Object* surface;
    Camera* cam;
    Portal* otherPortal;
    unsigned int fbo, rbo, finalTex;
    unsigned long int* temptex;
};