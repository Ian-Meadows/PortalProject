#include "Wall.h"

Wall::Wall(Vector3D pos,  Vector3D scale, Vector3D rotation) :
 Surface(pos, scale, rotation){
     std::vector<std::string> texture = {"Images/crate.bmp"};
     std::vector<bool> hasAlpha = {false};
        LoadTextures(texture, hasAlpha);
}