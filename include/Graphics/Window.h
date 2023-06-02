#ifndef WINDOW_H
#define WINDOW_H


#include <string>

#include "includes.h"
#include "Print.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <math.h>

#include "FrameTime.h"
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

    Window(int argc, char *argv[], WindowInfo& info, void (*reshape)(GLFWwindow*,int,int), void (*key)(GLFWwindow*,int,int,int,int));
    ~Window();

    void Start();

    void Draw();
    void Reshape(int width, int height);
    void KeyInput(int key, int scancode, int action, int mods);

    static void ErrCheck(const char* where);

private:

    WindowInfo info;
    GLFWwindow *window;

    int pitch = 0;
    int yaw = 300;
    Camera* camera = nullptr;
    

    void ResetView();

    GLFWwindow* InitWindow(const std::string title,int sync,int width,int height , void (*reshape)(GLFWwindow*,int,int) , void (*key)(GLFWwindow*,int,int,int,int));

    double aspectRatio = 1;
    double worldDimension = 20.0;

    bool smoothShading = true;

    int width, height;

};


#endif