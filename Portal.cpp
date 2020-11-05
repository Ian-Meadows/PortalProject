#include "Portal.h"

Portal::Portal(Vector3D pos, Vector3D scale, Vector3D rotation) : Object(pos, scale, rotation)
{
    //implement texture for portal
}

void Portal::setOtherPortal(Portal *other)
{
    otherPortal = other;
}

void Portal::DrawShape()
{

    int rep = 5;

    float white[] = {1, 1, 1, 1};
    float black[] = {0, 0, 0, 1};
    float shiny = 1; // Shininess (value)
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shiny);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, white);
    glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, black);

    glEnable(GL_TEXTURE_2D);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    //glBindTexture(GL_TEXTURE_2D, textures[0]);

    glBegin(GL_QUADS);
    glColor3f(1, 1, 1);

    glNormal3f(0, 1, 0);

    glTexCoord2f(0, 0);
    glVertex3f(-1, 0, +1);
    glTexCoord2f(rep, 0);
    glVertex3f(+1, 0, +1);
    glTexCoord2f(rep, rep);
    glVertex3f(+1, 0, -1);
    glTexCoord2f(0, rep);
    glVertex3f(-1, 0, -1);

    glEnd();

    glDisable(GL_TEXTURE_2D);
}