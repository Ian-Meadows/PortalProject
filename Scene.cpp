#include "Scene.h"

//taken from ex7.c
#define LEN 8192 //  Maximum length of text string
void Print(const char *format, ...)
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

namespace Scene
{
    namespace
    {
        std::vector<Object *> objects;
        std::vector<Portal *> portals;

        Shader *shader;

        Vector3D size;
        void Draw3DGraph(double len)
        {
            glPushMatrix();
            glTranslated(-1.5, 0, 1.5);
            glScaled(3, 3, 3);

            //taken directly from ex7.c
            glColor3f(1, 1, 1);
            glBegin(GL_LINES);
            glVertex3d(0.0, 0.0, 0.0);
            glVertex3d(len, 0.0, 0.0);
            glVertex3d(0.0, 0.0, 0.0);
            glVertex3d(0.0, len, 0.0);
            glVertex3d(0.0, 0.0, 0.0);
            glVertex3d(0.0, 0.0, len);
            glEnd();
            //  Label axes
            glRasterPos3d(len, 0.0, 0.0);
            Print("X");
            glRasterPos3d(0.0, len, 0.0);
            Print("Y");
            glRasterPos3d(0.0, 0.0, len);
            Print("Z");

            glPopMatrix();
        }

        void InitScene()
        {

            shader = new Shader("Shaders/SceneShader.vert", "Shaders/SceneShader.frag");

            //light
            objects.push_back(new Light(Vector3D(0, 0, 0), 0.65));

            //portals
            Portal *p1 = new Portal(Vector3D(-2, 3, 5),
                                    Vector3D(2), Vector3D(90, 0, 180));

            Portal *p2 = new Portal(Vector3D(2, 3, -5),
                                    Vector3D(2), Vector3D(90, 0, 0));

            objects.push_back(p1);
            objects.push_back(p2);
            portals.push_back(p1);
            portals.push_back(p2);

            p1->setOtherPortal(p2);
            p2->setOtherPortal(p1);

            //simple
            objects.push_back(new SimpleObject(Vector3D(-1, -1, -3),
                                               Vector3D(0.2), Vector3D(45, 0, 0)));

            objects.push_back(new SimpleObject(Vector3D(1, 0, -3),
                                               Vector3D(0.4), Vector3D(0, 0, 45)));

            objects.push_back(new SimpleObject(Vector3D(0, 1, -3),
                                               Vector3D(0.3), Vector3D(0, 45, 0)));

            //complex

            objects.push_back(new ComplexObject(Vector3D(-3, 0, 0),
                                                Vector3D(1), Vector3D(35, 180, 25)));

            objects.push_back(new ComplexObject(Vector3D(),
                                                Vector3D(1), Vector3D(0, 0, 0)));

            //cube :)
            objects.push_back(new Companion(Vector3D(2, 0, 0),
                                            Vector3D(1), Vector3D(0, 0, 0)));

            //floor

            objects.push_back(new WhiteFloor(Vector3D(0, -1, 0),
                                             Vector3D(8, 1, 8), Vector3D(0, 0, 0)));
        }

    } // namespace

    void Init()
    {
        size = Vector3D(1, 1, 1);
        InitScene();
    }
    void Init(Vector3D size)
    {
        Scene::size = size;
        InitScene();
    }
    void CleanUp()
    {
        for (unsigned int i = 0; i < objects.size(); ++i)
        {
            if (objects[i] != nullptr)
            {
                delete objects[i];
            }
        }
    }

    void Draw(Camera *camera)
    {
        shader->use();
        glPushMatrix();
        {
            for (unsigned int i = 0; i < portals.size(); ++i)
            {
                glPushMatrix();
                {
                
                //TODO:: rotation is broken on the portals - FIX THIS
                glScaled(size.x, size.y, size.z);
                Vector3D pos, rot;
                portals[i]->enablePortalDrawing(pos, rot); //use the portal's framebuffer

                
                    
                Camera portalview(pos, rot); //Vector3D(0,1,0), spinny);
                                             //portalview.Draw();
                Vector3D viewDirection;
                // used information from : https : //learnopengl.com/Getting-started/Camera
                viewDirection.x = Cos(rot.x) * Cos(rot.z);
                viewDirection.y = Sin(rot.z);
                viewDirection.z = Sin(rot.x) * Cos(rot.z);

                //get the up vector
                Vector3D up = viewDirection.Normalize().Cross(viewDirection.Normalize().Cross(Vector3D(0, -1, 0)));
                //add the position vector to the front vector
                Vector3D added = pos.Add(viewDirection.Normalize());

                //change view matrix
                 gluLookAt(pos.x, pos.y, pos.z, //camera position
                          added.x, added.y, added.z,          //position + direction
                          up.x, up.y, up.z); 
                //up

                for (unsigned int i = 0; i < objects.size(); ++i)
                {
                    glColor3f(1, 1, 1);
                    objects[i]->Draw();
                }
                glBindFramebuffer(GL_FRAMEBUFFER, 0); //reset to the default framebuffer
                }
                glPopMatrix();
            }
            //Draw3DGraph(3.5);
        }
        glPopMatrix();

        glPushMatrix();
        {
            glLoadIdentity();
            camera->Draw();
            glScaled(size.x, size.y, size.z);
            for (unsigned int i = 0; i < objects.size(); ++i)
            {
                glColor3f(1, 1, 1);
                objects[i]->Draw();
            }
        }
        glPopMatrix();
    }

    void SetSceneSize(Vector3D size)
    {
        Scene::size = size;
    }
    Vector3D GetSceneSize()
    {
        return size;
    }
} // namespace Scene