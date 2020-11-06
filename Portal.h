#pragma once
#include "Object.h"

class Portal : public Object
{
public:
    Portal(Vector3D pos, Vector3D scale, Vector3D rotation);
    void setOtherPortal(Portal* other);
    void enablePortalDrawing();

    ~Portal();

private:
    void DrawShape();

    Portal* otherPortal;
    unsigned int fbo, rbo;
};