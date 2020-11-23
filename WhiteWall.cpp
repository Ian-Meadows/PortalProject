#include "WhiteWall.h"

WhiteWall::WhiteWall(Vector3D pos,  Vector3D scale, Vector3D rotation) :
 Wall(pos, scale, rotation, {"Images/concrete_modular_wall1.bmp"}, {true}){
     //std::vector<std::string> texture = {"Images/concrete_modular_wall1.bmp"};
     //std::vector<bool> hasAlpha = {true};
        //LoadTextures(texture, hasAlpha);
}

bool WhiteWall::portalable()
{
    return true;
}