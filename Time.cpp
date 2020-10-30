#include "Time.h"
#include <iostream>
#include <GL/glut.h>


namespace Time{
    namespace{
        double deltaTime;
        int currentFPS;
        int FPS;

        double currentFrame;
        double lastFrame;

        double currentTime = 0;

        bool debug;
    }

    double GetFPS(){
        return FPS;
    }

    double GetDeltaTime(){
        return deltaTime;
    }

    void Init(bool debug){
        deltaTime = 0;
        FPS = 0;
        currentFrame = glutGet(GLUT_ELAPSED_TIME) / 1000;
        lastFrame = glutGet(GLUT_ELAPSED_TIME) / 1000;
        Time::debug = debug;
    }

    void Update(){
        lastFrame = currentFrame;
        currentFrame = glutGet(GLUT_ELAPSED_TIME) / 1000;
        deltaTime = currentFrame - lastFrame;

        currentTime += deltaTime;


        if(currentTime >= 1.0){
            FPS = currentFPS;
            currentFPS = 0;
            if(debug){
                std::cout << FPS << std::endl;
            }
            currentTime = 0;
        }
        currentFPS++;

    }


}


