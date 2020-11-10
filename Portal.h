#pragma once
#include "Object.h"

#define PORTAL_WIDTH 1024
#define PORTAL_HEIGHT 1024

class Portal : public Object
{
public:
    Portal(Vector3D pos, Vector3D scale, Vector3D rotation);
    void setOtherPortal(Portal* other);
    void enablePortalDrawing(Vector3D &pos, Vector3D &rot);
    void endPortalDrawing();

    ~Portal();

private:
    void DrawShape();

    Portal* otherPortal;
    unsigned int fbo, rbo, finalTex;
    unsigned int* temptex;
};