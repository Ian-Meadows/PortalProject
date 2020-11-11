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
        Shader *portalShader;

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

        //takes: 0,0,0
        Vector3D GetVectorFromString(std::string str)
        {
            std::string numbers[3] = {"", "", ""};
            std::string delim = ",";
            auto start = 0U;
            auto end = str.find(delim);

            int index = 0;

            while (end != std::string::npos && index < 2)
            {
                //std::cout << objLine.substr(start, end - start) << std::endl;

                numbers[index] = str.substr(start, end - start);

                start = end + delim.length();
                end = str.find(delim, start);
                index++;
            }
            numbers[index] = str.substr(start, end);
            Vector3D vec;
            if (index == 1)
            {
                vec = Vector3D(stod(numbers[0]));
            }
            else
            {
                vec = Vector3D(stod(numbers[0]), stod(numbers[1]), stod(numbers[2]));
            }

            return vec;
        }

        void LoadObject(std::string objLine)
        {
            std::string settings[4] = {"", "", "", ""};
            std::string delim = " ";
            auto start = 0U;
            auto end = objLine.find(delim);

            int index = 0;

            while (end != std::string::npos && index < 3)
            {
                //std::cout << objLine.substr(start, end - start) << std::endl;

                settings[index] = objLine.substr(start, end - start);
                std::cout << settings[index] << std::endl;

                start = end + delim.length();
                end = objLine.find(delim, start);
                index++;
            }
            settings[index] = objLine.substr(start, end);
            std::cout << settings[index] << std::endl;

            std::string objName = settings[0];
            if (objName == "")
            {
                return;
            }

            Vector3D pos;
            Vector3D rot;
            Vector3D scale(1, 1, 1);
            if (index >= 1)
            {
                pos = GetVectorFromString(settings[1]);
            }
            if (index >= 2)
            {
                rot = GetVectorFromString(settings[2]);
            }
            if (index >= 3)
            {
                scale = GetVectorFromString(settings[3]);
            }

            //spawn objects
            if (objName == "WhiteFloor")
            {
                objects.push_back(new WhiteFloor(pos, scale, rot));
            }
            else if (objName == "WhiteWall")
            {
                objects.push_back(new WhiteWall(pos, scale, rot));
            }
            else if (objName == "SimpleObject")
            {
                objects.push_back(new SimpleObject(pos, scale, rot));
            }
            else if (objName == "ComplexObject")
            {
                objects.push_back(new ComplexObject(pos, scale, rot));
            }
            else if (objName == "Companion")
            {
                objects.push_back(new Companion(pos, scale, rot));
            }
            else if (objName == "BlackFloor")
            {
                objects.push_back(new BlackFloor(pos, scale, rot));
            }
            else if (objName == "BlackWall")
            {
                objects.push_back(new BlackWall(pos, scale, rot));
            }
            else
            {
                std::cout << "ERROR:[" << objName << "] does not exist" << std::endl;
            }
        }

        void SceneFileReader(std::string filePath)
        {
            std::ifstream file(filePath);
            // open files
            if (file.is_open())
            {
                std::string line;
                while (getline(file, line))
                {
                    LoadObject(line);
                }
                file.close();
            }
        }

        void InitScene()
        {

            shader = new Shader("Shaders/SceneShader.vert", "Shaders/SceneShader.frag");
            portalShader = new Shader("Shaders/PortalShader.vert", "Shaders/PortalShader.frag");

            portalShader->use();
            portalShader->setFloat("sizeY", 0.85);
            portalShader->setFloat("sizeX", 0.5f);
            portalShader->setFloat("offset", 0.07f);

            //light
            objects.push_back(new Light(Vector3D(0, 0, 0), 0.65));

            //portals
            Portal *p1 = new Portal(Vector3D(-2, 3, 9),
                                    Vector3D(2), Vector3D(0, 90, 0));

            Portal *p2 = new Portal(Vector3D(2, 3, -9),
                                    Vector3D(2), Vector3D(0, -90, 0));

            portals.push_back(p1);
            portals.push_back(p2);

            p1->setOtherPortal(p2);
            p2->setOtherPortal(p1);

            //read in the rest of the scene from file
            SceneFileReader("SceneInfo.txt");
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

    void renderPortals(Vector3D initcampos)
    {
        glViewport(0, 0, PORTAL_WIDTH, PORTAL_HEIGHT);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluPerspective(55, 1, 0.1f, 100);
        glMatrixMode(GL_MODELVIEW);
        glPushMatrix();
        {
            for (unsigned int i = 0; i < portals.size(); ++i)
            {
                glPushMatrix();
                {

                    //initcampos.Print("campos1: ");
                    //TODO:: adjust portal view based on user view
                    glScaled(size.x, size.y, size.z);
                    Vector3D pos, rot, thisrot, thispos;
                    portals[i]->enablePortalDrawing(pos, rot, thispos, thisrot);  //use the portal's framebuffer, also get rot of this portal and pos and rot of other portal
                    //thispos.Print("thispos: ");
                    //thisrot.Print("thisrot: ");
                    //get camera vector to portal and normalize it
                    Vector3D campos = thispos.Subtract(initcampos);
                    //campos = campos.Normalize(); // <apparently breaks everything
                    //campos.Print("campos2: ");

                    //reflect camera vector off of portal plane
                    Vector3D portalNormal; //get normal of the portal
                    portalNormal.x = Cos(thisrot.y) * Cos(thisrot.x);
                    portalNormal.y = Sin(thisrot.x);
                    portalNormal.z = Sin(thisrot.y) * Cos(thisrot.x);

                    portalNormal = portalNormal.Normalize();
                    //portalNormal.Print("normal: ");

                    //std::cout << "dot:" << campos.Dot(portalNormal) << std::endl;

                    //Vector3D tempviewDirection = ((portalNormal + campos) * -2 * (campos.Dot(portalNormal))).Normalize(); //reflection of camera view vector off of current portal
                    Vector3D pivot = portalNormal.Normalize().Cross(portalNormal.Normalize().Cross(Vector3D(0, -1, 0)));
                    //Vector3D newNormal = portalNormal*Cos(-90)+(pivot.Cross(portalNormal))*Sin(-90)+pivot*(pivot.Dot(portalNormal)*(1-Cos(-90)));
                    //Vector3D viewDirection = ((newNormal + tempviewDirection) * 2 * (tempviewDirection.Dot(newNormal))).Normalize();

                    Vector3D viewDirection = (campos * Cos(180) + (pivot.Cross(campos)) * Sin(180) + pivot * (pivot.Dot(campos) * (1 - Cos(180)))).Normalize();

                    //Vector3D viewDirection = tempviewDirection*Cos(180)+(portalNormal.Cross(tempviewDirection))*Sin(180)+portalNormal*(portalNormal.Dot(tempviewDirection)*(1-Cos(180)));
                    //viewDirection.Rotate(thisrot);
                    //portalNormal.Rotate(Vector3D(0,-90,0));
                    //viewDirection = ((portalNormal + viewDirection) * -2 * (viewDirection.Dot(portalNormal))).Normalize(); //reflection of camera view vector off of current portal
                    //viewDirection.Print("viewDirection1: ");
                    // apply rotation difference to vector to map it to other portal
                    Vector3D rotdiff = rot.Subtract(thisrot);
                    viewDirection.Rotate(rotdiff);
                    //viewDirection.Print("viewDirection2: ");
                    //add vector to position of the other portal
                    Vector3D added = pos.Add(viewDirection.Normalize());
                    //viewDirection.Print("added: ");

                    // used information from : https : //learnopengl.com/Getting-started/Camera

                    //get the up vector
                    Vector3D up = viewDirection.Normalize().Cross(viewDirection.Normalize().Cross(Vector3D(0, -1, 0)));
                    //add the position vector to the front vector

                    //change view matrix
                    gluLookAt(pos.x, pos.y, pos.z,       //camera position
                              added.x, added.y, added.z, //position + direction
                              up.x, up.y, up.z);
                    //up
                    shader->use();
                    for (unsigned int j = 0; j < objects.size(); ++j)
                    {
                        glColor3f(1, 1, 1);
                        objects[j]->Draw();
                    }
                    portalShader->use();
                    
                    for (unsigned int j = 0; j < portals.size(); ++j)
                    {
                        portalShader->setInt("portalNumber", j);
                        glColor3f(1, 1, 1);
                        portals[j]->Draw();
                        //portalShader->setInt("portalNumber", 1);
                    }
                    portals[i]->endPortalDrawing(); //reset to the default framebuffer
                }
                glPopMatrix();
            }
            //Draw3DGraph(3.5);
        }
        glPopMatrix();
    }

    void Draw(Camera *camera)
    {

        glPushMatrix();
        {
            shader->use();
            camera->Draw();
            glScaled(size.x, size.y, size.z);
            for (unsigned int i = 0; i < objects.size(); ++i)
            {
                glColor3f(1, 1, 1);
                objects[i]->Draw();
            }
            portalShader->use();
            for (unsigned int i = 0; i < portals.size(); ++i)
            {
                portalShader->setInt("portalNumber", i);
                glColor3f(1, 1, 1);
                portals[i]->Draw();
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