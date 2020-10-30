#include "Light.h"



Light::Light(Vector3D pos,  double size) :
    Object(pos, Vector3D(size, size, size), Vector3D()){

}

Light::~Light(){

}


void Light::DrawShape(){

    UpdatePosition();

    //taken from ex13
    int th,ph;
    float yellow[] = {1.0,1.0,0.0,1.0};
    float Emission[]  = {0.0,0.0,0.01f*emission,1.0};
    //  Save transformation
    glPushMatrix();
    //  Offset, scale and rotate
    glTranslated(position.x, position.y, position.z);
    glScaled(scale.x, scale.y, scale.z);
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


    lightPos[0] = distance*Cos(zh);
    lightPos[1] = position.y;
    lightPos[2] = distance*Sin(zh);
    lightPos[3] = 1.0;
    // = {distance*Cos(zh), position.y, distance*Sin(zh), 1.0};


    position.x = lightPos[0];
    position.y = lightPos[1];
    position.z = lightPos[2];


    
}

void Light::UpdateLighting(){
    if(lighting){
        //  Translate intensity to color vectors
        float Ambient[]   = {0.01f*ambient ,0.01f*ambient ,0.01f*ambient ,1.0f};
        float Diffuse[]   = {0.01f*diffuse ,0.01f*diffuse ,0.01f*diffuse ,1.0f};
        float Specular[]  = {0.01f*specular,0.01f*specular,0.01f*specular,1.0f};
        //  OpenGL should normalize normal vectors
        glEnable(GL_NORMALIZE);
        //  Enable lighting
        glEnable(GL_LIGHTING);
        //  Location of viewer for specular calculations
        glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, local);
        //  glColor sets ambient and diffuse color materials
        glColorMaterial(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE);
        glEnable(GL_COLOR_MATERIAL);
        //  Enable light 0
        glEnable(GL_LIGHT0);
        //  Set ambient, diffuse, specular components and position of light 0
        glLightfv(GL_LIGHT0,GL_AMBIENT ,Ambient);
        glLightfv(GL_LIGHT0,GL_DIFFUSE ,Diffuse);
        glLightfv(GL_LIGHT0,GL_SPECULAR,Specular);
        glLightfv(GL_LIGHT0,GL_POSITION,lightPos);
    }
}