#include "MovingLight.h"


MovingLight::MovingLight(LightInfo li) : Light(li)
{
}

MovingLight::~MovingLight()
{
}


void MovingLight::DrawShape(){

    //taken from ex13
    int th,ph;
    //  Save transformation
    glPushMatrix();
    //  Offset, scale and rotate
    Vector3D position = GetPosition();
    glTranslated(position.x, position.y, position.z);
    glScaled(0.1, 0.1, 0.1);
    //  White ball
    glColor3f(1,1,1);
   

    

    //  Bands of latitude
    for (ph=-90;ph<90;ph+=inc)
    {
        glBegin(GL_QUAD_STRIP);
        for (th=0;th<=360;th+=2*inc)
        {
            Vertex(th,ph);
            Vertex(th,ph+inc);
        }
        glEnd();
    }
    //  Undo transofrmations
    

    
   glPopMatrix();
}

void MovingLight::Vertex(double th, double ph){
   double x = Sin(th)*Cos(ph);
   double y = Cos(th)*Cos(ph);
   double z =         Sin(ph);
   //  For a sphere at the origin, the position
   //  and normal vectors are the same
   glNormal3d(x,y,z);
   glVertex3d(x,y,z);
}


void MovingLight::ChangePosition(int zh){

    Vector3D newPos(distance*Cos(zh), GetPosition().y, distance*Sin(zh));
    SetPosition(newPos);

}