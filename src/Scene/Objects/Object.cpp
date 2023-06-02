#include "Object.h"

Object::Object(Vector3D pos, Vector3D scale, Vector3D rotation){
    position = pos;
    this->scale = scale;
    this->rotation = rotation;
    FixRotation();
}
Object::~Object(){
    if(textures != nullptr){
        delete[] textures;
    }
}

void Object::Draw(Shader* shader){
    

    if(shader != nullptr){
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, textures[0]);
        
        shader->setInt("hasNormalMap", hasNormalMap);
        if(hasNormalMap){
            glActiveTexture(GL_TEXTURE1);
            glBindTexture(GL_TEXTURE_2D, normalMap);
        }
        
    }

    //  Save transformation
    glPushMatrix();
    //  Offset and scale
    
    glTranslated(position.x, position.y, position.z);
    glRotated(rotation.x,1,0,0);
    glRotated(rotation.y,0,1,0);
    glRotated(rotation.z,0,0,1);
    glScaled(scale.x, scale.y, scale.z);
    

    glActiveTexture(GL_TEXTURE0);
    DrawShape();
    if(shader != nullptr){
        shader->setInt("tex", 0);
        shader->setInt("normalMap", 1);
        
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(position.x, position.y, position.z));
        model = glm::rotate(model, glm::radians((float)rotation.x), glm::vec3(1.0, 0.0, 0.0));
        model = glm::rotate(model, glm::radians((float)rotation.y), glm::vec3(0.0, 1.0, 0.0));
        model = glm::rotate(model, glm::radians((float)rotation.z), glm::vec3(0.0, 0.0, 1.0));
        model = glm::scale(model, glm::vec3(scale.x, scale.y, scale.z));
        
        shader->setMat4("model", model);
    }
    

    //  Undo transformations
    glPopMatrix();
}

void Object::DrawShape(){

}


    Vector3D Object::getPosition()
    {
        return position;
    }
    Vector3D Object::getScale()
    {
        return scale;
    }
    Vector3D Object::getRotation()
    {
        return rotation;
    }


void Object::LoadTextures(std::vector<std::string> textureFiles, std::vector<bool> hasAlpha, std::string normalMap){
    if(textureFiles.size() != hasAlpha.size()){
        std::cout << "ERROR: texture files does not equal hasAlpha list" << std::endl;
    }
    textures = new unsigned int[textureFiles.size()];

    for(unsigned int i = 0; i < textureFiles.size(); ++i){
        textures[i] = TextureHandler::LoadTexture(textureFiles[i], hasAlpha[i]);\
    }

    if(normalMap != ""){
        this->normalMap = TextureHandler::LoadTexture(normalMap, true);
        hasNormalMap = true;
    }
    else{
        hasNormalMap = false;
    }
    



}

void Object::UpdateRotation(Vector3D rotation){
    this->rotation = rotation;
    FixRotation();
}

//should I add recursion?
void Object::FixRotation(){
    //x
    if(rotation.x < 0){
        rotation.x = 360 + rotation.x;
    }
    if(rotation.x > 360){
        rotation.x = 0 + rotation.x;
    }

    //y
    if(rotation.y < 0){
        rotation.y = 360 + rotation.y;
    }
    if(rotation.y > 360){
        rotation.y = 0 + rotation.y;
    }

    //z
    if(rotation.z < 0){
        rotation.z = 360 + rotation.z;
    }
    if(rotation.z > 360){
        rotation.z = 0 + rotation.z;
    }
}