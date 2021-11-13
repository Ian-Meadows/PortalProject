//This file is just the launcher file for the most part. Window handles the rest of the functionality

#include <stdio.h>
#include "includes.h"

#include "Window.h"
#include "Time.h"
#include "LightHandler.h"

static Window *window;

static void draw()
{
    window->Draw();
}

void key(GLFWwindow* w, int key, int scancode, int action, int mods)
{

    window->KeyInput(key, scancode, action, mods);
    
}


//
// Main program with GLFW event loop
//
int main(int argc, char *argv[])
{

    WindowInfo windowInfo(0, 0, 1280, 720, "Portal: Andrew Hack, Ian Meadows");

    window = new Window(argc, argv, windowInfo, &key);

    window->Start();

    delete window;

    return 0;
}