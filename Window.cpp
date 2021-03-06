#include "Window.h"

#define LEN 8192 //  Maximum length of text string
void Window::Print(const char *format, ...)
{
    char buf[LEN];
    char *ch = buf;
    va_list args;
    //  Turn the parameters into a character string
    va_start(args, format);
    vsnprintf(buf, LEN, format, args);
    va_end(args);
    //  Display the characters one at a time at the current raster position
    while (*ch)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *ch++);
}

Window::Window(int argc, char *argv[], WindowInfo &info)
{

    camera = new Camera();

    //more initializations to glut
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE | GLUT_STENCIL);

    glutInitWindowPosition(info.xPos, info.yPos);
    glutInitWindowSize(info.xSize, info.ySize);


    



    win = glutCreateWindow(info.name.c_str());

    Time::Init(false);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);

    Scene::Init(Vector3D(1), camera);
}

Window::~Window()
{
    Scene::CleanUp();
    glutDestroyWindow(win);
    delete camera;
}

void Window::Start()
{
    glutMainLoop();
}

//taken from ex.5
void Window::ErrCheck(const char *where)
{
    int err = glGetError();
    if (err)
        fprintf(stderr, "ERROR: %s [%s]\n", gluErrorString(err), where);
}

void Window::Draw()
{

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);

    glEnable(GL_STENCIL_TEST);
    glStencilMask(0x00);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
     

    glLoadIdentity();

    glShadeModel(smoothShading ? GL_SMOOTH : GL_FLAT);

    Reshape(width, height);
    Scene::Draw(camera);

    Scene::renderPortals(camera, 5);

    ErrCheck("display");
    glFlush();
    glutSwapBuffers();
}

void Window::Reshape(int w, int h)
{

    width = w;
    height = h;
    if (height > 0)
    {
        aspectRatio = (double)width / (double)height;
    }
    else
    {
        aspectRatio = 1;
    }

    glViewport(0, 0, (GLint)width, (GLint)height);
    if (camera != nullptr)
    {
        camera->UpdateProjection(worldDimension, aspectRatio, width, height);
    }
}


void Window::KeyInput(unsigned char k, int x, int y)
{
    if (k == '0')
    {
        ResetView();
    }
    //portal move keys
    else if (k == '1')
    {
        Scene::setPortalsLocation(1);
    }
    else if (k == '2')
    {
        Scene::setPortalsLocation(2);
    }
    else if (k == '3')
    {
        Scene::setPortalsLocation(3);
    }
    else if (k == '4')
    {
        Scene::setPortalsLocation(4);
    }
    else if (k == '5')
    {
        Scene::setPortalsLocation(5);
    }

    if (camera != nullptr)
    {
        camera->KeyPressed(k, x, y);

        camera->UpdateProjection(worldDimension, aspectRatio, width, height);
    }
    if(k == 'r')
    {
        std::cout << "Refreshing the scene according to the file" << std::endl;
        Scene::refreshScene();
    }

    glutPostRedisplay();
}

//taken from ex7.c
void Window::SpecialKeyInput(int key, int x, int y)
{

    if (camera != nullptr)
    {
        camera->SpecialKeyPressed(key, x, y);

        camera->UpdateProjection(worldDimension, aspectRatio, width, height);
    }

    //  Tell GLUT it is necessary to redisplay the scene
    glutPostRedisplay();
}

//set back to initial view
void Window::ResetView()
{
    pitch = 0;
    yaw = 300;
}
