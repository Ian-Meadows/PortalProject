#include "LightHandler.h"


namespace LightHandler{
    namespace{
        std::vector<Light*> lights;
        Shader* shader;

        double       Svec[4];   // Texture planes S
        double       Tvec[4];   // Texture planes T
        double       Rvec[4];   // Texture planes R
        double       Qvec[4];   // Texture planes Q
        float        Lpos[4];   // Light position

        unsigned int framebuf=0;
        int          shadowdim;

        void ShadowMap(){
            double Lmodel[16];  //  Light modelview matrix
            double Lproj[16];   //  Light projection matrix
            double Tproj[16];   //  Texture projection matrix
            double Dim=10.0;     //  Bounding radius of scene
            double Ldist;       //  Distance from light to scene center

            //  Save transforms and modes
            glPushMatrix();
            glPushAttrib(GL_TRANSFORM_BIT|GL_ENABLE_BIT);
            //  No write to color buffer and no smoothing
            glShadeModel(GL_FLAT);
            glColorMask(0,0,0,0);
            // Overcome imprecision
            glEnable(GL_POLYGON_OFFSET_FILL);

            //  Turn off lighting and set light position
            Light(0);

            //  Light distance
            Ldist = sqrt(Lpos[0]*Lpos[0] + Lpos[1]*Lpos[1] + Lpos[2]*Lpos[2]);
            if (Ldist<1.1*Dim) Ldist = 1.1*Dim;

            //  Set perspective view from light position
            glMatrixMode(GL_PROJECTION);
            glLoadIdentity();
            gluPerspective(114.6*atan(Dim/Ldist),1,Ldist-Dim,Ldist+Dim);
            glMatrixMode(GL_MODELVIEW);
            glLoadIdentity();
            gluLookAt(Lpos[0],Lpos[1],Lpos[2] , 0,0,0 , 0,1,0);
            //  Size viewport to desired dimensions
            glViewport(0,0,shadowdim,shadowdim);

            // Redirect traffic to the frame buffer
            glBindFramebuffer(GL_FRAMEBUFFER,framebuf);

            // Clear the depth buffer
            glClear(GL_DEPTH_BUFFER_BIT);
            // Draw all objects that can cast a shadow
            Scene::DrawShadowableObjects();

            //  Retrieve light projection and modelview matrices
            glGetDoublev(GL_PROJECTION_MATRIX,Lproj);
            glGetDoublev(GL_MODELVIEW_MATRIX,Lmodel);

            // Set up texture matrix for shadow map projection,
            // which will be rolled into the eye linear
            // texture coordinate generation plane equations
            glLoadIdentity();
            glTranslated(0.5,0.5,0.5);
            glScaled(0.5,0.5,0.5);
            glMultMatrixd(Lproj);
            glMultMatrixd(Lmodel);

            // Retrieve result and transpose to get the s, t, r, and q rows for plane equations
            glGetDoublev(GL_MODELVIEW_MATRIX,Tproj);
            Svec[0] = Tproj[0];    Tvec[0] = Tproj[1];    Rvec[0] = Tproj[2];    Qvec[0] = Tproj[3];
            Svec[1] = Tproj[4];    Tvec[1] = Tproj[5];    Rvec[1] = Tproj[6];    Qvec[1] = Tproj[7];
            Svec[2] = Tproj[8];    Tvec[2] = Tproj[9];    Rvec[2] = Tproj[10];   Qvec[2] = Tproj[11];
            Svec[3] = Tproj[12];   Tvec[3] = Tproj[13];   Rvec[3] = Tproj[14];   Qvec[3] = Tproj[15];

            // Restore normal drawing state
            glShadeModel(GL_SMOOTH);
            glColorMask(1,1,1,1);
            glDisable(GL_POLYGON_OFFSET_FILL);
            glPopAttrib();
            glPopMatrix();
            glBindFramebuffer(GL_FRAMEBUFFER,0);
        }

        void InitShadowMap(){
            unsigned int shadowtex; //  Shadow buffer texture id
            int n;

            //  Make sure multi-textures are supported
            glGetIntegerv(GL_MAX_TEXTURE_UNITS,&n);
            if (n<2){
                //Fatal("Multiple textures not supported\n");
                std::cout << "Multiple textures not supported" << std::endl;
            } 
            

            //  Get maximum texture buffer size
            glGetIntegerv(GL_MAX_TEXTURE_SIZE,&shadowdim);
            //  Limit texture size to maximum buffer size
            glGetIntegerv(GL_MAX_RENDERBUFFER_SIZE,&n);
            if (shadowdim>n) shadowdim = n;
            //  Limit texture size to 2048 for performance
            if (shadowdim>2048) shadowdim = 2048;
            if (shadowdim<512){
                //Fatal("Shadow map dimensions too small %d\n",shadowdim);
                std::cout << "Shadow map dimensions too small" << std::endl;
            } 

            //  Do Shadow textures in MultiTexture 1
            glActiveTexture(GL_TEXTURE1);

            //  Allocate and bind shadow texture
            glGenTextures(1,&shadowtex);
            glBindTexture(GL_TEXTURE_2D,shadowtex);
            glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT24, shadowdim, shadowdim, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);

            //  Map single depth value to RGBA (this is called intensity)
            glTexParameteri(GL_TEXTURE_2D,GL_DEPTH_TEXTURE_MODE,GL_INTENSITY);

            //  Set texture mapping to clamp and linear interpolation
            glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);

            //  Set automatic texture generation mode to Eye Linear
            glTexGeni(GL_S,GL_TEXTURE_GEN_MODE,GL_EYE_LINEAR);
            glTexGeni(GL_T,GL_TEXTURE_GEN_MODE,GL_EYE_LINEAR);
            glTexGeni(GL_R,GL_TEXTURE_GEN_MODE,GL_EYE_LINEAR);
            glTexGeni(GL_Q,GL_TEXTURE_GEN_MODE,GL_EYE_LINEAR);

            // Switch back to default textures
            glActiveTexture(GL_TEXTURE0);

            // Attach shadow texture to frame buffer
            glGenFramebuffers(1,&framebuf);
            glBindFramebuffer(GL_FRAMEBUFFER,framebuf);
            glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, shadowtex, 0);
            //  Don't write or read to visible color buffer
            glDrawBuffer(GL_NONE);
            glReadBuffer(GL_NONE);
            //  Make sure this all worked
            if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE){
                std::cout << "Error setting up frame buffer" << std::endl;
                //Fatal("Error setting up frame buffer\n");

            } 
            glBindFramebuffer(GL_FRAMEBUFFER,0);

            //  Check if something went wrong
            Window::ErrCheck("InitMap");

            //  Create shadow map
            ShadowMap();
        }
    }



    void Init(Shader* shader){

        LightHandler::shader = shader;

        Vector3D pos = Vector3D(7, 5, 0);
        AddLight(LightInfo(GL_LIGHT0, pos));

        //temp 
        Lpos[0] = pos.x;
        Lpos[1] = pos.y;
        Lpos[2] = pos.z;
        Lpos[3] = 1.0;



        //AddLight(LightInfo(GL_LIGHT1, Vector3D(-5, 1, 5)));
        //AddLight(LightInfo(GL_LIGHT2, Vector3D(5, 1, 5)));

        InitShadowMap();
    }


    void Update(bool isLighting){
        if(isLighting){
            glEnable(GL_NORMALIZE);
            glEnable(GL_LIGHTING);

            glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, 0);
            //  glColor sets ambient and diffuse color materials
            glColorMaterial(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE);
            glEnable(GL_COLOR_MATERIAL);


            glActiveTexture(GL_TEXTURE1);
            glTexGendv(GL_S,GL_EYE_PLANE,Svec);
            glTexGendv(GL_T,GL_EYE_PLANE,Tvec);
            glTexGendv(GL_R,GL_EYE_PLANE,Rvec);
            glTexGendv(GL_Q,GL_EYE_PLANE,Qvec);
            glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_COMPARE_MODE,GL_COMPARE_R_TO_TEXTURE);
            glActiveTexture(GL_TEXTURE0);

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