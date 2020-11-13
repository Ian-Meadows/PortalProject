#include "LightHandler.h"


namespace LightHandler{
    namespace{
        std::vector<Light*> lights;
        Shader* shader;
    }



    void Init(Shader* shader){

        LightHandler::shader = shader;

        AddLight(LightInfo(GL_LIGHT0, Vector3D(7, 10, 0)));
        AddLight(LightInfo(GL_LIGHT1, Vector3D(-5, 1, 5)));
        AddLight(LightInfo(GL_LIGHT2, Vector3D(5, 1, 5)));
    }


    void Update(bool isLighting){
        if(isLighting){
            glEnable(GL_NORMALIZE);
            glEnable(GL_LIGHTING);

            glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, 0);
            //  glColor sets ambient and diffuse color materials
            glColorMaterial(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE);
            glEnable(GL_COLOR_MATERIAL);


            for(int i = 0; i < lights.size(); ++i){
                lights[i]->DrawShape();
            }

        }
        
    }



    void AddLight(LightInfo lightInfo){
        Light* light = new Light(lightInfo);
        lights.push_back(light);
    }



    void CleanUp(){
        for(int i = 0; i < lights.size(); ++i){
            delete lights[i];
        }
        lights.clear();
    }
}