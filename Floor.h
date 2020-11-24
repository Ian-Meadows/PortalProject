#ifndef FLOOR_H
#define FLOOR_H


#include "Surface.h"


class Floor : public Surface{
public:
    Floor(Vector3D pos, Vector3D scale, Vector3D rotation, std::vector<std::string> textures, std::vector<bool> hasAlphas);
    ~Floor();

};


#endif