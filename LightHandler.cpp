#include "LightHandler.h"

//taken from ex36
void Project(double fov,double asp,double dim)
{
   //  Tell OpenGL we want to manipulate the projection matrix
   glMatrixMode(GL_PROJECTION);
   //  Undo previous transformations
   glLoadIdentity();
   //  Perspective transformation
   if (fov)
      gluPerspective(fov,asp,dim/16,16*dim);
   //  Orthogonal transformation
   else
      glOrtho(-asp*dim,asp*dim,-dim,+dim,-dim,+dim);
   //  Switch to manipulating the model matrix
   glMatrixMode(GL_MODELVIEW);
   //  Undo previous transformations
   glLoadIdentity();
}

namespace LightHandler{
    namespace{
        std::vector<Light*> lights;
        Shader* shader;

        Vector3D ambientLight;

        Camera* camera;

        
    }
        



    void Init(Shader* shader, Vector3D ambientLight, Camera* camera){
        LightHandler::camera = camera;
        LightHandler::shader = shader;

        Vector3D pos = Vector3D(7, 5, 0);
        //AddLight(LightInfo(GL_LIGHT0, pos));
        AddMovingLight(LightInfo(GL_LIGHT0, pos));


        LightHandler::ambientLight = ambientLight;

        //AddLight(LightInfo(GL_LIGHT1, Vector3D(-5, 1, 5)));
        //AddLight(LightInfo(GL_LIGHT2, Vector3D(5, 1, 5)));
    }


    void Update(bool isLighting){
        if(isLighting){

            
            
            glEnable(GL_NORMALIZE);

            //glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, 0);
            //  glColor sets ambient and diffuse color materials
            glColorMaterial(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE);
            glEnable(GL_COLOR_MATERIAL);
            glDisable(GL_LIGHTING);

            for(unsigned int i = 0; i < lights.size(); ++i){
                lights[i]->Draw(ambientLight, shader);
            }
            glEnable(GL_LIGHTING);

        }
        
    }



    void AddLight(LightInfo lightInfo){
        Light* light = new Light(lightInfo);
        lights.push_back(light);
    }

    void AddMovingLight(LightInfo lightInfo){
        MovingLight* light = new MovingLight(lightInfo);
        lights.push_back(light);
    }



    void CleanUp(){
        for(unsigned int i = 0; i < lights.size(); ++i){
            delete lights[i];
        }
        lights.clear();
    }
}