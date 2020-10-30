#ifndef WINDOW_H
#define WINDOW_H

#define GL_GLEXT_PROTOTYPES
#include <string>
#include <GL/glut.h>

#include "Scene.h"
#include "Camera.h"


struct WindowInfo{
    int xPos;
    int yPos;

    int xSize;
    int ySize;

    std::string name;

    WindowInfo(){
        xPos = 0;
        yPos = 0;

        xSize = 300;
        ySize = 300;

        name = "No Name";
    }

    WindowInfo(int xPos, int yPos, int xSize, int ySize, std::string name){
        this->xPos = xPos;
        this->yPos = yPos;

        this->xSize = xSize;
        this->ySize = ySize;

        this->name = name;
    }

    WindowInfo(WindowInfo* windowInfo){
        this->xPos = windowInfo->xPos;
        this->yPos = windowInfo->yPos;

        this->xSize = windowInfo->xSize;
        this->ySize = windowInfo->ySize;

        this->name = windowInfo->name;
    }
};


class Window{

public:

    Window(int argc, char *argv[], WindowInfo& info);
    ~Window();

    void Start();

    void Draw();
    void Reshape(int width, int height);
    void KeyInput(unsigned char k, int x, int y);
    void SpecialKeyInput(int k, int x, int y);

private:

    GLint win;

    WindowInfo info;

    int pitch = 0;
    int yaw = 300;


    Scene* scene;
    Camera* camera = nullptr;
    

    void ResetView();

    void ErrCheck(const char* where);

    void Print(const char* format, ...);

    double aspectRatio = 1;
    double worldDimension = 20.0;

    bool smoothShading = true;
    

};


#endif