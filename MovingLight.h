#ifndef MOVING_LIGHT_H
#define MOVING_LIGHT_H
#include "Light.h"

class MovingLight : public Light
{

public:
    MovingLight(LightInfo li);
    ~MovingLight();

protected:
    void DrawShape();
    void ChangePosition(int zh);


private:
    void Vertex(double th, double ph);
    int distance = 5;
    int inc       =  10;  // Ball increment
};






#endif