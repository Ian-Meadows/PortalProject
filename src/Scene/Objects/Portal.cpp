#include "Portal.h"

Portal::Portal(Vector3D pos, Vector3D scale, Vector3D rotation) : Object(pos, scale, rotation)
{
    
}

void Portal::setOtherPortal(Portal *other)
{
    otherPortal = other;
}

Portal *Portal::getOtherPortal()
{
    return otherPortal;
}

void Portal::enablePortalDrawing(Vector3D &pos, Vector3D &rot, Vector3D &thispos, Vector3D &thisrot)
{
    pos = otherPortal->getPosition();
    rot = otherPortal->getRotation();
    thisrot = getRotation();
    thispos = getPosition();
}

Portal::~Portal()
{
}

void Portal::DrawShape()
{
    GLdouble portalsize = 0.95, edgesize = 1;
    float white[] = {1, 1, 1, 1};
    float black[] = {0, 0, 0, 1};
    float shiny = 1; // Shininess (value)
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shiny);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, white);
    glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, black);

    glEnable(GL_TEXTURE_2D);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glEnable(GL_POLYGON_OFFSET_FILL);

    // oval shape
    glPushMatrix();
    {
        glPolygonOffset(-3, -3);
        glBegin(GL_TRIANGLE_FAN);

        glNormal3f(0, 0, 1);
        glTexCoord2f(0.5, 0.5);
        glVertex3f(0, 0, 0); //set center point for top circle
        int angleChange = 5;

        for (int ang = 360; ang >= 0; ang -= angleChange) //draw circle in chunks
        {
            glTexCoord2f(Sin(ang) / 2 + 0.5, Cos(ang) / 2 + 0.5);
            ovalVertex(ang, portalsize, portalsize);
            glTexCoord2f(Sin(ang - angleChange) / 2 + 0.5, Cos(ang - angleChange) / 2 + 0.5);
            ovalVertex(ang - angleChange, portalsize, portalsize);
        }
        glEnd();
    }
    glPopMatrix();

    glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);

    glBegin(GL_TRIANGLE_FAN);

    glNormal3f(0, 0, -1);
    glTexCoord2f(0.5, 0.5);
    glVertex3f(0, 0, 0); //set center point for top circle
    int angleChange = 5;

    for (int ang = 360; ang >= 0; ang -= angleChange) //draw circle in chunks
    {
        glTexCoord2f(Sin(ang) / 2 + 0.5, Cos(ang) / 2 + 0.5);
        ovalVertex(ang, edgesize, edgesize);
        glTexCoord2f(Sin(ang - angleChange) / 2 + 0.5, Cos(ang - angleChange) / 2 + 0.5);
        ovalVertex(ang - angleChange, edgesize, edgesize);
    }
    glEnd();
    glPolygonOffset(0, 0);

    glDisable(GL_TEXTURE_2D);

    glDisable(GL_POLYGON_OFFSET_FILL);
}

void Portal::setCam(Camera *c)
{
    cam = c;
}

Camera *Portal::getCam()
{
    return cam;
}

void Portal::setSurface(Object *s)
{
    surface = s;
}

Object *Portal::getSurface()
{
    return surface;
}

void Portal::updateSpot(Vector3D pos, Vector3D rot)
{
    position = pos;
    rotation = rot; 
    FixRotation();
}
