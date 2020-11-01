#include "BlackWall.h"

BlackWall::BlackWall(Vector3D pos,  Vector3D scale, Vector3D rotation) :
 Wall(pos, scale, rotation){
     std::vector<std::string> texture = {"Images/metalwall1.bmp"};
     std::vector<bool> hasAlpha = {true};
        LoadTextures(texture, hasAlpha);
}