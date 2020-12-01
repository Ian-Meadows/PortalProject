
#include "Vine.h"

Vine::Vine(Vector3D pos, Vector3D scale, Vector3D rotation) : Object(pos, scale, rotation)
{
    std::vector<std::string> texture = {"Images/white_wall_tile001a.bmp", "Images/metalwall1_lrg.bmp"};
    std::vector<bool> hasAlpha = {true, true};
    LoadTextures(texture, hasAlpha);
}
