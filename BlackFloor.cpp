#include "BlackFloor.h"

BlackFloor::BlackFloor(Vector3D pos,  Vector3D scale, Vector3D rotation) :
 Floor(pos, scale, rotation, {"Images/metal_modular_floor1.bmp"}, {true}){
     //std::vector<std::string> texture = {"Images/metal_modular_floor1.bmp"};
     //std::vector<bool> hasAlpha = {true};
        //LoadTextures(texture, hasAlpha);
}