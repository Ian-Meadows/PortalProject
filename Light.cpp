#include "Light.h"



Light::Light(LightInfo info){
    li = info;
}

Light::~Light(){

}


void Light::Draw(Vector3D ambientLight, Shader* shader){
    UpdatePosition();
    glUseProgram(0);
    glDisable(GL_LIGHTING);
    DrawShape();
    glEnable(GL_LIGHTING);
    shader->use();
    UpdateLighting(ambientLight);
}


void Light::DrawShape(){
    

    //taken from ex13
    int th,ph;
    //  Save transformation
    glPushMatrix();
    //  Offset, scale and rotate
    glTranslated(li.position.x, li.position.y, li.position.z);
    glScaled(0.1, 0.1, 0.1);
    //  White ball
    glColor3f((float)li.lightObjectColor.x, (float)li.lightObjectColor.y, (float)li.lightObjectColor.z);


   

    

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

void Light::ChangePosition(int zh)
{

}

//taken from ex13
void Light::Vertex(double th, double ph){
   double x = Sin(th)*Cos(ph);
   double y = Cos(th)*Cos(ph);
   double z =         Sin(ph);
   //  For a sphere at the origin, the position
   //  and normal vectors are the same
   glNormal3d(x,y,z);
   glVertex3d(x, y, z);
}

void Light::UpdatePosition(){
    double t = glfwGetTime() /1000.0;
    int zh = fmod(90*t,360.0);

    ChangePosition(zh);
    
}


void Light::SetPosition(Vector3D position){
    li.position = position;
}

void Light::UpdateLighting(Vector3D ambientLight){

    float lightPos[] = {(float)li.position.x, (float)li.position.y, (float)li.position.z, 1.0f};
    float Ambient[]   = {(float)ambientLight.x, (float)ambientLight.y, (float)ambientLight.z, 1.0f};
    float Diffuse[]   = {(float)li.diffuse.x, (float)li.diffuse.y, (float)li.diffuse.z, 1.0f};
    float Specular[]  = {(float)li.specular.x, (float)li.specular.y, (float)li.specular.z, 1.0f};
    
    //  Enable light 0
    glEnable(li.lightNumber);
    //  Set ambient, diffuse, specular components and position of light 0
    glLightfv(li.lightNumber,GL_AMBIENT, Ambient);
    glLightfv(li.lightNumber,GL_DIFFUSE, Diffuse);
    glLightfv(li.lightNumber,GL_SPECULAR, Specular);
    glLightfv(li.lightNumber,GL_POSITION, lightPos);
}