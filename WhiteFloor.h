#pragma once

#include "Floor.h"

class WhiteFloor : public Floor
{
    private:
    public:
    WhiteFloor(Vector3D pos, Vector3D scale, Vector3D rotation);
    bool portalable();
};