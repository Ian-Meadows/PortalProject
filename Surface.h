#pragma once
#include "Object.h"

class Surface : public Object
{
public:
    Surface(Vector3D pos, Vector3D scale, Vector3D rotation, std::vector<std::string> textures, std::vector<bool> hasAlphas);
    bool portalable();

    

private:
    void DrawShape();
    bool FileExists(std::string path);
};