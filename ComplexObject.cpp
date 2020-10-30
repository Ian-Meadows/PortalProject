#include "ComplexObject.h"

ComplexObject::ComplexObject(Vector3D pos, Vector3D scale, Vector3D rotation) :
 Object(pos, scale, rotation){
     std::vector<std::string> texture = {"Images/CrystalImage.bmp"};
     std::vector<bool> hasAlpha = {true};
        LoadTextures(texture, hasAlpha);
}
ComplexObject::~ComplexObject(){

}

Vector3D GenerateNormal(Vector3D p1, Vector3D p2, Vector3D p3){
    Vector3D A = p2.Subtract(p1);
    Vector3D B = p3.Subtract(p1);
    Vector3D normal;
    normal = A.Cross(B);
    return normal;
}

void ComplexObject::DrawTriangle(int i, Vector3D color){
    

    Vector3D p1 = Vector3D(xyz[index[(i * 3)]*3], xyz[index[(i * 3)]*3 + 1], xyz[index[(i * 3)]*3 + 2]);
    Vector3D p2 = Vector3D(xyz[index[(i * 3) + 1]*3], xyz[index[(i * 3) + 1]*3 + 1], xyz[index[(i * 3) + 1]*3 + 2]);
    Vector3D p3 = Vector3D(xyz[index[(i * 3) + 2]*3], xyz[index[(i * 3) + 2]*3 + 1], xyz[index[(i * 3) + 2]*3 + 2]);

    Vector3D normal = GenerateNormal(p1, p2, p3);
    glNormal3f( normal.x, normal.y, normal.z);
    
    glTexCoord2f(0.5, 0); glVertex3f(p1.x, p1.y, p1.z);
    glTexCoord2f(0, 1); glVertex3f(p2.x, p2.y, p2.z);
    glTexCoord2f(1, 1); glVertex3f(p3.x, p3.y, p3.z);
}


void ComplexObject::DrawShape(){

    glEnable(GL_TEXTURE_2D);
    glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glBindTexture(GL_TEXTURE_2D, textures[0]);
    glBegin(GL_TRIANGLES);
    glColor4f(1, 1, 1, 0.7);
    for(int i = 0; i < 16; ++i){
        
        DrawTriangle(i, Vector3D(0.75, 0, 1));
        
    }
    glEnd();
    glDisable(GL_TEXTURE_2D);
}