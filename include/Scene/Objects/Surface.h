#pragma once
#include "Object.h"

class Surface : public Object
{
public:
    Surface(Vector3D pos, Vector3D scale, Vector3D rotation, std::vector<std::string> textures, std::vector<bool> hasAlphas, std::string normalMap);
    bool portalable();

    

private:
    void DrawShape() override;
    bool FileExists(std::string path);
};