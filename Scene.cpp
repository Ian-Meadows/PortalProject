#include "Scene.h"


//taken from ex7.c
#define LEN 8192  //  Maximum length of text string
void Print(const char* format, ...)
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



namespace Scene{
    namespace{
        std::vector<Object*> objects;

        Shader* shader;

        Vector3D size;
        void Draw3DGraph(double len){
            glPushMatrix();
            glTranslated(-1.5, 0, 1.5);
            glScaled(3, 3, 3);

            //taken directly from ex7.c
            glColor3f(1,1,1);
            glBegin(GL_LINES);
            glVertex3d(0.0,0.0,0.0);
            glVertex3d(len,0.0,0.0);
            glVertex3d(0.0,0.0,0.0);
            glVertex3d(0.0,len,0.0);
            glVertex3d(0.0,0.0,0.0);
            glVertex3d(0.0,0.0,len);
            glEnd();
            //  Label axes
            glRasterPos3d(len,0.0,0.0);
            Print("X");
            glRasterPos3d(0.0,len,0.0);
            Print("Y");
            glRasterPos3d(0.0,0.0,len);
            Print("Z");

            glPopMatrix();
        }


        //takes: 0,0,0
        Vector3D GetVectorFromString(std::string str){
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
            if(index == 1){
                vec = Vector3D(stod(numbers[0]));
            }
            else{
                vec = Vector3D(stod(numbers[0]), stod(numbers[1]), stod(numbers[2]));
            }

            

            return vec;
        }

        void LoadObject(std::string objLine){
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
            if(objName == ""){
                return;
            }

            Vector3D pos;
            Vector3D rot;
            Vector3D scale(1, 1, 1);
            if(index >= 1){
                pos = GetVectorFromString(settings[1]);
            }
            if(index >= 2){
                rot = GetVectorFromString(settings[2]);
            }
            if(index >= 3){
                scale = GetVectorFromString(settings[3]);
            }

            //spawn objects
            if(objName == "WhiteFloor"){
                objects.push_back(new WhiteFloor(pos, scale, rot));
            }
            else if(objName == "WhiteWall"){
                objects.push_back(new WhiteWall(pos, scale, rot));
            }
            else if(objName == "SimpleObject"){
                objects.push_back(new SimpleObject(pos, scale, rot));
            }
            else if(objName == "ComplexObject"){
                objects.push_back(new ComplexObject(pos, scale, rot));
            }
            else if(objName == "Companion"){
                objects.push_back(new Companion(pos, scale, rot));
            }
            else if(objName == "BlackFloor"){
                objects.push_back(new BlackFloor(pos, scale, rot));
            }
            else if(objName == "BlackWall"){
                objects.push_back(new BlackWall(pos, scale, rot));
            }
            else{
                std::cout << "ERROR:[" << objName << "] does not exist" <<std::endl;
            }

        }



        void SceneFileReader(std::string filePath){
            std::ifstream file(filePath);
            // open files
            if(file.is_open()){
                std::string line;
                while(getline(file, line)){
                    LoadObject(line);
                }
                file.close();
            }
        }

        void InitScene(){

            shader = new Shader("Shaders/SceneShader.vert", "Shaders/SceneShader.frag");

            

            //light
            objects.push_back(new Light(Vector3D(0, 0, 0), 0.65));

            SceneFileReader("SceneInfo.txt");

            /*
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
            objects.push_back(new Companion(Vector3D(2,0,0),
                Vector3D(1), Vector3D(0, 0, 0)));

            //floor
            
            objects.push_back(new WhiteFloor(Vector3D(0, -2.5, 0),
                Vector3D(8, 1, 8), Vector3D(0, 0, 0)));
            */
            
        }

        



    }


    void Init(){
        size = Vector3D(1, 1, 1);
        InitScene();
    }
    void Init(Vector3D size){
        Scene::size = size;
        InitScene();
    }
    void CleanUp(){
        for(unsigned int i = 0; i < objects.size(); ++i){
            if(objects[i] != nullptr){
                delete objects[i];
            }
            
        }
    }


    void Draw(){
        shader->use();
        glScaled(size.x, size.y, size.z);

        //Draw3DGraph(3.5);

        for(unsigned int i = 0; i < objects.size(); ++i){
            glColor3f(1, 1, 1);
            objects[i]->Draw();
        }
    }


    void SetSceneSize(Vector3D size){
        Scene::size = size;
    }
    Vector3D GetSceneSize(){
        return size;
    }
}