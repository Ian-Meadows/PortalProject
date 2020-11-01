#include "Scene.h"


//taken from ex7.c
#define LEN 8192  //  Maximum length of text string
void Print(const char* format, ...)
{
   char    buf[LEN];
   char*   ch=buf;
   va_list args;
   //  Turn the parameters into a character string
   va_start(args,format);
   vsnprintf(buf,LEN,format,args);
   va_end(args);
   //  Display the characters one at a time at the current raster position
   while (*ch)
      glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,*ch++);
}



Scene::Scene(){
    size = Vector3D(1, 1, 1);
    InitScene();
}
Scene:: Scene(Vector3D size){
    this->size = size;
    InitScene();
}
Scene::~Scene(){
    for(unsigned int i = 0; i < objects.size(); ++i){
        if(objects[i] != nullptr){
            delete objects[i];
        }
        
    }
}


void Scene::Draw(){

    glScaled(size.x, size.y, size.z);

    //Draw3DGraph(3.5);

    for(unsigned int i = 0; i < objects.size(); ++i){
        objects[i]->Draw();
    }
}


void Scene::InitScene(){
    
    //light
    objects.push_back(new Light(Vector3D(0, 0, 0), 0.65));


    
    //simple
    objects.push_back(new SimpleObject(Vector3D(-1, -1, -3),
         Vector3D(0.2), Vector3D(45, 0, 0)));
    
    objects.push_back(new SimpleObject(Vector3D(1, 0, -3),
         Vector3D(0.4), Vector3D(0, 0, 45)));
    
    objects.push_back(new SimpleObject(Vector3D(0, 1, -3),
         Vector3D(0.3), Vector3D(0, 45, 0)));
    
    //complex

    objects.push_back(new ComplexObject(Vector3D(-3, 0, 0),
         Vector3D(1), Vector3D(35, 180, 25)));
    

    objects.push_back(new ComplexObject(Vector3D(),
         Vector3D(1), Vector3D(0, 0, 0)));


    //cube :)
    objects.push_back(new Companion(Vector3D(2,0,0),
         Vector3D(1), Vector3D(0, 0, 0)));

    //floor
    
    objects.push_back(new WhiteFloor(Vector3D(0, -2.5, 0),
         Vector3D(8, 1, 8), Vector3D(0, 0, 0)));
    




    
    
}

void Scene::Draw3DGraph(double len){

    glPushMatrix();
    glTranslated(-1.5, 0, 1.5);
    glScaled(3, 3, 3);

    //taken directly from ex7.c
    glColor3f(1,1,1);
    glBegin(GL_LINES);
    glVertex3d(0.0,0.0,0.0);
    glVertex3d(len,0.0,0.0);
    glVertex3d(0.0,0.0,0.0);
    glVertex3d(0.0,len,0.0);
    glVertex3d(0.0,0.0,0.0);
    glVertex3d(0.0,0.0,len);
    glEnd();
    //  Label axes
    glRasterPos3d(len,0.0,0.0);
    Print("X");
    glRasterPos3d(0.0,len,0.0);
    Print("Y");
    glRasterPos3d(0.0,0.0,len);
    Print("Z");

    glPopMatrix();
}



void Scene::SetSceneSize(Vector3D size){
    this->size = size;
}
Vector3D Scene::GetSceneSize(){
    return size;
}