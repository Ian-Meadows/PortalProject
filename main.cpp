//This file is just the launcher file for the most part. Window handles the rest of the functionality

#include <stdio.h>
#include <GL/glut.h>

#include "Window.h"
#include "Time.h"
#include "LightHandler.h"

static Window* window;


static void CleanUp(){
    //std::cout << "clean up----------------------------------------------" << std::endl;
    delete window;
    //std::cout << "clean up----------------------------------------------" << std::endl;
}


static void draw(){
    window->Draw();
}
static void reshape(int width, int height){
    window->Reshape(width, height);
}
static void key(unsigned char k, int x, int y){

    window->KeyInput(k, x, y);

    //ESC
    if(k == 27){
        CleanUp();
        exit(0);
    }
}
static void special(int k, int x, int y){
    window->SpecialKeyInput(k, x, y);
}

static void idle(){
    Time::Update();
    glutPostRedisplay();
}


int main(int argc, char *argv[])
{

    WindowInfo windowInfo(0, 0, 1280, 720, "Portal: Andrew Hack, Ian Meadows");

    window = new Window(argc, argv, windowInfo);

    //taken from ex7.c and gears.c
    glutDisplayFunc(draw);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(key);
    glutSpecialFunc(special);
    glutIdleFunc(idle);

    window->Start();

    delete window;

    return 0;
}