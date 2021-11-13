#include "Window.h"

Window::Window(int argc, char *argv[], WindowInfo &info, void (*reshape)(GLFWwindow*,int,int), void (*key)(GLFWwindow*,int,int,int,int))
{
    window = InitWindow(info.name, 1,info.xSize, info.ySize, reshape, key); //1 enables vsync
    camera = new Camera();

    Time::Init(false);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);

    Scene::Init(Vector3D(1), camera);
}

Window::~Window()
{
    Scene::CleanUp();
    glfwDestroyWindow(window);
    delete camera;
}

void Window::Start()
{
    while(!glfwWindowShouldClose(window))
    {
        //do that drawing thing
        this->Draw();
        //process events
        glfwPollEvents();
        //IDK, time or something?
        Time::Update();
    }
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
    glfwSwapBuffers(window);
}

void Window::Reshape(int w, int h)
{
    glfwGetFramebufferSize(window, &w, &h);
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

void Window::KeyInput(int key, int scancode, int action, int  mods)
{
    if (key == GLFW_KEY_0)
    {
        ResetView();
    }
    //portal move keys
    else if (key == GLFW_KEY_1)
    {
        Scene::setPortalsLocation(1);
    }
    else if (key == GLFW_KEY_2)
    {
        Scene::setPortalsLocation(2);
    }
    else if (key == GLFW_KEY_3)
    {
        Scene::setPortalsLocation(3);
    }
    else if (key == GLFW_KEY_4)
    {
        Scene::setPortalsLocation(4);
    }
    else if (key == GLFW_KEY_5)
    {
        Scene::setPortalsLocation(5);
    }

    if (camera != nullptr)
    {
        camera->KeyPressed(key, scancode, action, mods);

        camera->UpdateProjection(worldDimension, aspectRatio, width, height);
    }
    if(key == GLFW_KEY_R)
    {
        std::cout << "Refreshing the scene according to the file" << std::endl;
        Scene::refreshScene();
    }
    if (key == GLFW_KEY_ESCAPE)
    {
        delete this;
        exit(0);
    }

}

//set back to initial view
void Window::ResetView()
{
    pitch = 0;
    yaw = 300;
}

static void error(int error,const char* text)
{
    fprintf(stderr,"GLFW error %d: %s\n",error,text);
}

GLFWwindow* Window::InitWindow(const std::string title,int sync,int width,int height , void (*reshape)(GLFWwindow*,int,int) , void (*key)(GLFWwindow*,int,int,int,int))
{
   //  Initialize GLFW
   if (!glfwInit())
   {
       std::cout << "Cannot initialize glfw" << std::endl;
       exit(1);
   }

   //  Error callback
   glfwSetErrorCallback(error);

   //  Set window properties
   glfwWindowHint(GLFW_RESIZABLE,1);     //  Window can be resized
   glfwWindowHint(GLFW_DOUBLEBUFFER,1);  //  Window has double buffering
   glfwWindowHint(GLFW_DEPTH_BITS,24);   //  Prefer 24 depth bits
   glfwWindowHint(GLFW_ALPHA_BITS,8);    //  Prefer 8 alpha bits
   glfwWindowHint(GLFW_STENCIL_BITS,8);
#ifdef APPLE_GL4
   //  Apple specific window properties to use with GLEW
   glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
   glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2); 
   glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);
   glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT,GL_TRUE);
#endif

   //  Create window and make current
   GLFWwindow* window = glfwCreateWindow(width,height,title.c_str(), NULL, NULL);
   if (!window) 
   {
       std::cout << "Cannot create GLFW window" << std::endl;
       exit(1);
   }
   glfwMakeContextCurrent(window);

   //  Enable VSYNC (if selected)
   glfwSwapInterval(sync);

   #ifdef USEGLEW
   //  Initialize GLEW (if compiled in)
   if (glewInit()!=GLEW_OK)
   {
       std::cout << "Error initializing GLEW" << std::endl;
       exit(1);
   }
   #endif

   //TODO: figure out the resize shenanigans
   //  Set callback for window resize and make initial call
   /*
   if (reshape)
   {
      glfwSetWindowSizeCallback(window,reshape);
      //  Set initial window size and call reshape
      glfwGetWindowSize(window,&width,&height);
      reshape(window,width,height);
   }
   */

   //  Set callback for keyboard input
   if (key) glfwSetKeyCallback(window,key);

   //  Return window
   return window;
}
