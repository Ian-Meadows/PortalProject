#include "Window.h"

#define LEN 8192  //  Maximum length of text string
void Window::Print(const char* format, ...)
{
   char    buf[LEN];
   char*   ch=buf;
   va_list args;
   //  Turn the parameters into a character string
   va_start(args,format);
   vsnprintf(buf,LEN,format,args);
   va_end(args);
   //  Display the characters one at a time at the current raster position
   while (*ch)
      glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,*ch++);
}

Window::Window(int argc, char *argv[], WindowInfo& info){

    camera = new Camera();

    //more initializations to glut
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);

    glutInitWindowPosition(info.xPos, info.yPos);
    glutInitWindowSize(info.xSize, info.ySize);

    

    win = glutCreateWindow(info.name.c_str());

    Time::Init(false);

    

    scene = new Scene(Vector3D(3, 3, 3));
    
}

Window::~Window(){
    delete scene;
    glutDestroyWindow(win);
    delete camera;
}

void Window::Start(){
    glutMainLoop();
}

//taken from ex.5
void Window::ErrCheck(const char* where)
{
   int err = glGetError();
   if (err) fprintf(stderr,"ERROR: %s [%s]\n",gluErrorString(err),where);
}


void Window::Draw(){

    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

    glEnable(GL_DEPTH_TEST);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    glLoadIdentity();

    glShadeModel(smoothShading ? GL_SMOOTH : GL_FLAT);

    camera->Draw();
    

    scene->Draw();
    
    //draw text to screen
    glDisable(GL_LIGHTING);
    glDisable(GL_DEPTH_TEST);
    glColor3f(1,1,1);
    glWindowPos2i(5,5);
    Print("Projection: %s", camera->GetProjectionType().c_str());

    std::string str = "display";
    ErrCheck(str.c_str());
    glFlush();
    glutSwapBuffers();
}

void Window::Reshape(int width, int height){

    
    if(height > 0){
        aspectRatio = (double)width / (double)height;
    }
    else{
        aspectRatio = 1;
    }
    

    glViewport(0, 0, (GLint) width, (GLint) height);
    if(camera != nullptr){
        camera->UpdateProjection(worldDimension, aspectRatio);
    }
    
}

void Window::KeyInput(unsigned char k, int x, int y){
    if(k == '0'){
        ResetView();
    }

    if(camera != nullptr){
        camera->KeyPressed(k, x, y);

        camera->UpdateProjection(worldDimension, aspectRatio);
    }
    

    glutPostRedisplay();
}

//taken from ex7.c
void Window::SpecialKeyInput(int key, int x, int y){
    //  Right arrow key - increase angle by 5 degrees
   if (key == GLUT_KEY_RIGHT)
      yaw -= 5;
   //  Left arrow key - decrease angle by 5 degrees
   else if (key == GLUT_KEY_LEFT)
      yaw += 5;
   //  Up arrow key - increase elevation by 5 degrees
   else if (key == GLUT_KEY_UP)
      pitch += 5;
   //  Down arrow key - decrease elevation by 5 degrees
   else if (key == GLUT_KEY_DOWN)
      pitch -= 5;
   //  Keep angles to +/-360 degrees
   yaw %= 360;
   pitch %= 360;

    if(camera != nullptr){
        camera->SpecialKeyPressed(key, x, y);

        camera->UpdateProjection(worldDimension, aspectRatio);
    }
    

   //  Tell GLUT it is necessary to redisplay the scene
   glutPostRedisplay();
}

//set back to initial view
void Window::ResetView(){
    pitch = 0;
    yaw = 300;
}


