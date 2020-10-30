#ifndef LIGHT_H
#define LIGHT_H

#include "Object.h"

class Light : public Object{
public:
    Light(Vector3D pos,  double size);
    ~Light();


private:
    void DrawShape();

    void Vertex(double th, double ph);

    void UpdatePosition();

    void UpdateLighting();

    int emission = 0;
    float shiny   =   1;
    int inc       =  10;  // Ball increment
    int ambient   =  10;  // Ambient intensity (%)
    int diffuse   =  50;  // Diffuse intensity (%)
    int specular  =   10;  // Specular intensity (%)
    int local     =   0;  // Local Viewer Model

    int distance = 3;

    float lightPos[4];

    bool lighting = true;
};


#endif