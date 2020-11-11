#pragma once
#include "Object.h"

#define PORTAL_WIDTH 2048
#define PORTAL_HEIGHT 2048

class Portal : public Object
{
public:
    Portal(Vector3D pos, Vector3D scale, Vector3D rotation);
    void setOtherPortal(Portal* other);
    void enablePortalDrawing(Vector3D &pos, Vector3D &rot, Vector3D &thispos, Vector3D &thisrot);
    void endPortalDrawing();

    ~Portal();

private:
    void DrawShape();

    Portal* otherPortal;
    unsigned int fbo, rbo, finalTex;
    unsigned long int* temptex;
};