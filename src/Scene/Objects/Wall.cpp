#include "Wall.h"

Wall::Wall(Vector3D pos,  Vector3D scale, Vector3D rotation, std::vector<std::string> textures, std::vector<bool> hasAlphas, std::string normalMap) :
 Surface(pos, scale, rotation, textures, hasAlphas, normalMap){

}