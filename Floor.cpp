#include "Floor.h"



Floor::Floor(Vector3D pos,  Vector3D scale, Vector3D rotation) :
 Surface(pos, scale, rotation){
     std::vector<std::string> texture = {"Images/crate.bmp"};
     std::vector<bool> hasAlpha = {false};
        LoadTextures(texture, hasAlpha);
}

Floor::~Floor(){

}
