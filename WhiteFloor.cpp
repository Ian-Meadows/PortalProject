#include "WhiteFloor.h"

WhiteFloor::WhiteFloor(Vector3D pos,  Vector3D scale, Vector3D rotation) :
 Floor(pos, scale, rotation){
     std::vector<std::string> texture = {"Images/concrete_modular_ceiling1.bmp"};
     std::vector<bool> hasAlpha = {true};
        LoadTextures(texture, hasAlpha);
}

bool WhiteFloor::portalable()
{
    return true;
}