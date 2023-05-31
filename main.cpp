//This file is just the launcher file for the most part. Window handles the rest of the functionality

#include <stdio.h>
#include "includes.h"

#include "Window.h"
#include "Time.h"
#include "LightHandler.h"

static Window *window;

void key(GLFWwindow* w, int key, int scancode, int action, int mods)
{
    //  Discard key releases (keeps PRESS and REPEAT)
    if (action == GLFW_RELEASE)
        return;
    window->KeyInput(key, scancode, action, mods);
    
}

void reshape(GLFWwindow* w, int width, int height)
{
    window->Reshape(width, height);
}


//
// Main program with GLFW event loop
//
int main(int argc, char *argv[])
{

    WindowInfo windowInfo(0, 0, 1280, 720, "Portal: Andrew Hack, Ian Meadows");

    window = new Window(argc, argv, windowInfo, &reshape, &key);

    window->Start();

    delete window;

    return 0;
}