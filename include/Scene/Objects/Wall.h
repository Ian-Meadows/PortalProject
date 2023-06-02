#pragma once

#include "Surface.h"

class Wall : public Surface
{
    public:
    Wall(Vector3D pos, Vector3D scale, Vector3D rotation, std::vector<std::string> texture, std::vector<bool> hasAlpha, std::string normalMap);

};