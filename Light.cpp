#include "Light.h"



Light::Light(LightInfo info){
    li = info;
}

Light::~Light(){

}


void Light::DrawShape(){

    UpdatePosition();

    float emission = 0;
    float shiny = 0;

    //taken from ex13
    int th,ph;
    float yellow[] = {1.0,1.0,0.0,1.0};
    float Emission[]  = {0.0,0.0,0.01f*emission,1.0};
    //  Save transformation
    glPushMatrix();
    //  Offset, scale and rotate
    glTranslated(li.position.x, li.position.y, li.position.z);
    glScaled(1, 1, 1);
    //  White ball
    glColor3f(1,1,1);
    glMaterialf(GL_FRONT, GL_SHININESS, shiny);
    glMaterialfv(GL_FRONT, GL_SPECULAR, yellow);
    glMaterialfv(GL_FRONT, GL_EMISSION, Emission);


   

    

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

    UpdateLighting();
}

//taken from ex13
void Light::Vertex(double th, double ph){
   double x = Sin(th)*Cos(ph);
   double y = Cos(th)*Cos(ph);
   double z =         Sin(ph);
   //  For a sphere at the origin, the position
   //  and normal vectors are the same
   glNormal3d(x,y,z);
   glVertex3d(x,y,z);
}

void Light::UpdatePosition(){
    double t = glutGet(GLUT_ELAPSED_TIME)/1000.0;
    int zh = fmod(90*t,360.0);


    //li.position.x = distance*Cos(zh);
    //li.position.y = li.position.y;
    //li.position.z = distance*Sin(zh);
    // = {distance*Cos(zh), position.y, distance*Sin(zh), 1.0};


    
}

void Light::UpdateLighting(){

    float lightPos[] = {li.position.x, li.position.y, li.position.z, 1.0f};
    float Ambient[]   = {li.ambient.x, li.ambient.y, li.ambient.z, 1.0f};
    float Diffuse[]   = {li.diffuse.x, li.diffuse.y, li.diffuse.z, 1.0f};
    float Specular[]  = {li.specular.x, li.specular.y, li.specular.z, 1.0f};
    
    //  Enable light 0
    glEnable(li.lightNumber);
    //  Set ambient, diffuse, specular components and position of light 0
    glLightfv(li.lightNumber,GL_AMBIENT, Ambient);
    glLightfv(li.lightNumber,GL_DIFFUSE, Diffuse);
    glLightfv(li.lightNumber,GL_SPECULAR, Specular);
    glLightfv(li.lightNumber,GL_POSITION, lightPos);
}