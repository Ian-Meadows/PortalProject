#include "MovingLight.h"


MovingLight::MovingLight(LightInfo li) : Light(li)
{
}

MovingLight::~MovingLight()
{
}


void MovingLight::DrawShape(){

    //float emission = 0;
    //float shiny = 0;

    //taken from ex13
    int th,ph;
    //float yellow[] = {1.0,1.0,0.0,1.0};
    //float Emission[]  = {0.0,0.0,0.01f*emission,1.0};
    //  Save transformation
    glPushMatrix();
    //  Offset, scale and rotate
    Vector3D position = GetPosition();
    glTranslated(position.x, position.y, position.z);
    glScaled(1, 1, 1);
    //  White ball
    glColor3f(1,1,1);
    //glMaterialf(GL_FRONT, GL_SHININESS, shiny);
    //glMaterialfv(GL_FRONT, GL_SPECULAR, yellow);
    //glMaterialfv(GL_FRONT, GL_EMISSION, Emission);
   

    

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
    //li.position.x = distance*Cos(zh);
    //li.position.y = li.position.y;
    //li.position.z = distance*Sin(zh);
    // = {distance*Cos(zh), position.y, distance*Sin(zh), 1.0};

    Vector3D newPos(distance*Cos(zh), GetPosition().y, distance*Sin(zh));
    SetPosition(newPos);

}