#pragma once

#include "Wall.h"

class WhiteWall : public Wall
{
    private:
    public:
    WhiteWall(Vector3D pos, Vector3D scale, Vector3D rotation);
    bool portalable();
};