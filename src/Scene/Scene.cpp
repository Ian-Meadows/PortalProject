#include "Scene.h"

//taken from ex7.c
#define LEN 8192 //  Maximum length of text string


namespace Scene
{
    namespace
    {
        std::vector<Object *> objects;
        std::vector<Portal *> portals;
        Camera *maincam = nullptr;

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
            //check if it is a comment line
            if (objLine[0] == '#')
            {
                return;
            }

            std::string settings[7] = {"", "", "", "", "", "", ""};
            std::string delim = " ";
            auto start = 0U;
            auto end = objLine.find(delim);

            int index = 0;

            while (end != std::string::npos && index < 6)
            {
                settings[index] = objLine.substr(start, end - start);

                start = end + delim.length();
                end = objLine.find(delim, start);
                index++;
            }
            settings[index] = objLine.substr(start, end);

            std::string objName = settings[0];
            if (objName == "")
            {
                return;
            }

            Vector3D pos;
            Vector3D rot;
            Vector3D scale(1, 1, 1);
            std::string texturePath = settings[4];
            bool hasAlpha;
            std::string normalMapPath = settings[6];

            //position
            if (index >= 1)
            {
                pos = GetVectorFromString(settings[1]);
            }
            //rotation
            if (index >= 2)
            {
                rot = GetVectorFromString(settings[2]);
            }
            //scale
            if (index >= 3)
            {
                scale = GetVectorFromString(settings[3]);
            }
            //texture alpha
            if (index >= 5)
            {
                if (settings[5] == "true")
                {
                    hasAlpha = true;
                }
                else if (settings[5] == "false")
                {
                    hasAlpha = false;
                }
                else
                {
                    std::cout << "ERROR: true or false does not exist setting alpha value to false" << std::endl;
                    hasAlpha = false;
                }
            }

            //spawn objects
            if (objName == "SimpleObject")
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
            else if (objName == "Dropper")
            {
                objects.push_back(new Dropper(pos, scale, rot));
            }
            else if (objName == "Observe")
            {
                objects.push_back(new Observe(pos, scale, rot));
            }
            else if (objName == "Floor")
            {
                objects.push_back(new Floor(pos, scale, rot, {texturePath}, {hasAlpha}, normalMapPath));
            }
            else if (objName == "Wall")
            {
                objects.push_back(new Wall(pos, scale, rot, {texturePath}, {hasAlpha}, normalMapPath));
            }
            else
            {
                std::cout << "ERROR:[" << objName << "] does not exist" << std::endl;
            }
        }

        void SceneFileReader(std::string filePath)
        {
            objects.clear();
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

        void InitScene(Camera *camera)
        {

            shader = new Shader("resources/Shaders/SceneShader.vert", "resources/Shaders/SceneShader.frag");
            portalShader = new Shader("resources/Shaders/PortalShader.vert", "resources/Shaders/PortalShader.frag");

            portalShader->use();
            portalShader->setFloat("sizeY", 0.85);
            portalShader->setFloat("sizeX", 0.5f);
            portalShader->setFloat("offset", 0.07f);

            //portals
            Portal *p1 = new Portal(Vector3D(0, 2, 10),
                                    Vector3D(1, 2, 1), Vector3D(0, 0, 0));

            Portal *p2 = new Portal(Vector3D(0, 2, -10),
                                    Vector3D(1, 2, 1), Vector3D(0, 180, 0));

            p1->setOtherPortal(p2);
            p2->setOtherPortal(p1);

            //read in the rest of the scene from file
            SceneFileReader("resources/Scenes/SceneInfo.txt");

            p1->setSurface(objects[2]);
            p2->setSurface(objects[3]);

            p1->setCam(new Camera());
            p2->setCam(new Camera());

            portals.push_back(p1);
            portals.push_back(p2);

            LightHandler::Init(shader, Vector3D(0.1), camera); 
        }

    } // namespace

//portal move keys
    void setPortalsLocation(int pos)
    {
        if (pos == 1)
        {
            portals[0]->updateSpot(Vector3D(0, 2, 10), Vector3D(0, 0, 0));
            portals[1]->updateSpot(Vector3D(0, 2, -10), Vector3D(0, 180, 0));
        }
        else if (pos == 2)
        {
            portals[0]->updateSpot(Vector3D(0, 2, 10), Vector3D(0, 0, 0));
            portals[1]->updateSpot(Vector3D(18, 2, -6), Vector3D(0, 90, 0));
        }
        else if (pos == 3)
        {
            portals[0]->updateSpot(Vector3D(8.585, 8.5, 8.585), Vector3D(0, 45, 0));
            portals[1]->updateSpot(Vector3D(0, 2, -10), Vector3D(0, 180, 0));
        }
        else if (pos == 4)
        {
            portals[0]->updateSpot(Vector3D(-10,2,9), Vector3D(0, -90, 0));
            portals[1]->updateSpot(Vector3D(-9, 2, 10), Vector3D(0, 0, 0));
        }
        else if (pos == 5)
        {
            portals[0]->updateSpot(Vector3D(-10,9,-1), Vector3D(0,-90,0));
            portals[1]->updateSpot(Vector3D(18, 2, -6), Vector3D(0, 90, 0));
        }
    }

    void refreshScene()
    {
        SceneFileReader("resources/Scenes/SceneInfo.txt");
    }

    void Init(Camera *camera)
    {
        size = Vector3D(1, 1, 1);
        InitScene(camera);
    }
    void Init(Vector3D size, Camera *camera)
    {
        Scene::size = size;
        InitScene(camera);
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

    void doportalrender(Camera *camera, int rec, int i)
    {
        glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);
        //stencil stuff
        glStencilFunc(GL_EQUAL, i * 50 + 1 + rec, 0xFF);
        glStencilMask(0xFF); //portal 1 is 1, portal 2 is 2

        glScaled(size.x, size.y, size.z);
        Vector3D pos, rot, thisrot, thispos;
        portals[i]->enablePortalDrawing(pos, rot, thispos, thisrot); //use the portal's framebuffer, also get rot of this portal and pos and rot of other portal

        //get camera vector to portal and normalize it
        Vector3D camdiff = camera->GetPosition().Subtract(thispos);

        //reflect camera vector off of portal plane
        Vector3D portalNormal; //get normal of the portal
        portalNormal.x = Cos(thisrot.y) * Cos(thisrot.x);
        portalNormal.y = Sin(thisrot.x);
        portalNormal.z = Sin(thisrot.y) * Cos(thisrot.x);

        portalNormal = portalNormal.Normalize();

        Vector3D pivot = portalNormal.Normalize().Cross(portalNormal.Normalize().Cross(Vector3D(0, -1, 0)));

        // apply rotation difference to vector to map it to other portal
        Vector3D rotdiff = rot.Subtract(thisrot);

        camdiff = camdiff.RotateAround(pivot, 180);
        camdiff = camdiff.Rotate(rotdiff);

        pos = pos.Add(camdiff);

        Camera *portalcam = portals[i]->getCam();

        portalcam->Update(pos, camera->GetRotation().Add(rotdiff.Negate()).Add(Vector3D(pivot.x * 180, pivot.y * 180, pivot.z * 180))); //update perspective so portal lines up with player
        portalcam->Draw();          //apply changes
        LightHandler::Update(true); //reset light after perspective has been moved

        //camera setup complete

        glClear(GL_DEPTH_BUFFER_BIT);
        //up
        shader->use();

        maincam->drawSelf();

        for (unsigned int j = 0; j < objects.size(); ++j)
        {
            glColor3f(1, 1, 1);
            objects[j]->Draw(shader);
        }

        portalShader->use();

        glStencilOp(GL_KEEP, GL_KEEP, GL_INCR);
        glStencilFunc(GL_EQUAL, i * 50 + 1 + rec, 0xFF);
        portalShader->setInt("portalNumber", i);
        glColor3f(1, 1, 1);
        portals[i]->Draw(nullptr);
    }

    void renderPortalsRec(int rec, int maxrec)
    {
        if (rec == maxrec)
            return;

        glPushMatrix();
        {
            for (unsigned int i = 0; i < portals.size(); ++i)
            {
                glPushMatrix();
                {
                    Camera *portalcam = portals[i]->getCam();
                    doportalrender(portalcam, rec, i);
                }
                glPopMatrix();
            }
        }
        glPopMatrix();
        renderPortalsRec(rec + 1, maxrec);
    }

    void renderPortals(Camera *camera, int rec)
    {

        glPushMatrix();
        {
            for (unsigned int i = 0; i < portals.size(); ++i)
            {
                glPushMatrix();
                {
                    portals[i]->getCam()->UpdateProjection(20.0, camera->GetAspectRatio(), camera->GetWidth(), camera->GetHeight());
                    doportalrender(camera, 0, i);
                }
                glPopMatrix();
            }
        }
        glPopMatrix();
        renderPortalsRec(1, rec);
    }

    void Draw(Camera *camera)
    {
        
        maincam = camera;
        glStencilFunc(GL_ALWAYS, 0, 0xFF);
        glStencilMask(0xFF);
        glPushMatrix();
        {
            shader->use();
            camera->Draw();
            glScaled(size.x, size.y, size.z);
            if (false)
            {
                glDisable(GL_LIGHTING);
                Draw3DGraph(10);
            }

            LightHandler::Update(true);
            
            shader->setVec3("viewPos", camera->GetPosition());
            for (unsigned int i = 0; i < objects.size(); ++i)
            {
                glColor3f(1, 1, 1);
                objects[i]->Draw(shader);
            }
            

            portalShader->use();
            for (unsigned int i = 0; i < portals.size(); ++i)
            {
                glStencilFunc(GL_ALWAYS, i * 50 + 1, 0xFF);
                glStencilMask(0xFF); //portal 1 is 1, portal 2 is 2
                glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
                portalShader->setInt("portalNumber", i);
                glColor3f(1, 1, 1);
                portals[i]->Draw(nullptr);
            }
            glStencilFunc(GL_ALWAYS, 0, 0xFF);
            glStencilMask(0xFF);
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