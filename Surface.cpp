#include "Surface.h"

Surface::Surface(Vector3D pos, Vector3D scale, Vector3D rotation, std::vector<std::string> textures, std::vector<bool> hasAlphas, std::string normalMap) : Object(pos, scale, rotation)
{
    if (textures.size() == 0)
    {
        textures.push_back("Images/crate.bmp");
        hasAlphas.push_back(false);
    }
    LoadTextures(textures, hasAlphas, normalMap);
}

bool Surface::portalable()
{
    return false;
}

void Surface::DrawShape()
{
    Vector3D scale = getScale();
    int s = 2;

    float white[] = {1, 1, 1, 1};
    float black[] = {0, 0, 0, 1};
    float shiny = 1; // Shininess (value)
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shiny);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, white);
    glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, black);

    glEnable(GL_TEXTURE_2D);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glBindTexture(GL_TEXTURE_2D, textures[0]);

    glBegin(GL_QUADS);
    glColor3f(1, 1, 1);

    glNormal3f(0, 0, -1);

    glTexCoord2f(0, scale.y/s);
    glVertex3f(+1, +1, 0);
    glTexCoord2f(0, 0);
    glVertex3f(+1, -1, 0);
    glTexCoord2f(scale.x/s, 0);
    glVertex3f(-1, -1, 0);
    glTexCoord2f(scale.x/s, scale.y/s);
    glVertex3f(-1, +1, 0);

    glEnd();

    glDisable(GL_TEXTURE_2D);
}

bool Surface::FileExists(std::string path)
{
    if (FILE *file = fopen(path.c_str(), "r"))
    {
        fclose(file);
        return true;
    }
    else
    {
        return false;
    }
}