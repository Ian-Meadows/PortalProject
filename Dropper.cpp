#include "Dropper.h"

Dropper::Dropper(Vector3D pos, Vector3D scale, Vector3D rotation) : Object(pos, scale, rotation)
{
    std::vector<std::string> texture = {"Images/box_dropper_tube.bmp", "Images/plasticwall001b.bmp", "Images/underground_wall_metal001a.bmp", "Images/metalwall1_lrg.bmp"};
    std::vector<bool> hasAlpha = {true, true, true, true};
    LoadTextures(texture, hasAlpha, "");
}

void Dropper::cylinder(GLint angleChange, GLdouble radius, GLdouble height)
{
    glBindTexture(GL_TEXTURE_2D, textures[0]);
    glPushMatrix();
    glScaled(radius, height, radius);

    glBegin(GL_QUADS);
    for (int ang = 0; ang <= 355; ang += angleChange)
    {
        glTexCoord2f(0.2, 0.25);
        cyliVertex(ang, 1);
        glTexCoord2f(0.8, 0.25);
        cyliVertex(ang + angleChange, 1);
        cyliVertex(ang + angleChange, -1);
        glTexCoord2f(0.2, 0.25);
        cyliVertex(ang, -1);
    }
    glEnd();

    glPopMatrix();
}

void Dropper::bottomring(GLint angleChange, GLdouble innerradius, GLdouble outerradius)
{
    GLdouble top = -0.7;
    GLdouble bott = -1;
    glBindTexture(GL_TEXTURE_2D, textures[1]);
    glPushMatrix();

    glBegin(GL_QUAD_STRIP);

    glNormal3f(0, 1, 0);
    glTexCoord2f(0.5, 0.5);

    for (int ang = 0; ang <= 360; ang += angleChange) //draw circle in chunks
    {
        glTexCoord2f(Sin(ang) / 2 + 0.5, Cos(ang) / 2 + 0.5);
        circleVertex(ang, bott, innerradius);
        glTexCoord2f(Sin(ang) / 2 + 0.5, Cos(ang) / 2 + 0.5);
        circleVertex(ang, bott, outerradius);
    }
    glEnd();

    glBegin(GL_QUAD_STRIP);

    glNormal3f(0, 1, 0);
    glTexCoord2f(0.5, 0.5);

    for (int ang = 360; ang >= 0; ang -= angleChange) //draw circle in chunks
    {
        glTexCoord2f(Sin(ang) / 2 + 0.5, Cos(ang) / 2 + 0.5);
        circleVertex(ang, top, innerradius);
        glTexCoord2f(Sin(ang) / 2 + 0.5, Cos(ang) / 2 + 0.5);
        circleVertex(ang, top, outerradius);
    }
    glEnd();

    //connect top circle to bottom circle
    glBegin(GL_QUADS);
    for (int ang = 0; ang <= 355; ang += angleChange)
    {
        glTexCoord2f(0.2, 0.25);
        cyliVertex(ang, top, outerradius);
        glTexCoord2f(0.8, 0.25);
        cyliVertex(ang + angleChange, top, outerradius);
        cyliVertex(ang + angleChange, bott, outerradius);
        glTexCoord2f(0.2, 0.25);
        cyliVertex(ang, bott, outerradius);
    }
    glEnd();

    glBegin(GL_QUADS);
    for (int ang = 355; ang >= 0; ang -= angleChange)
    {
        glTexCoord2f(0.2, 0.25);
        cyliVertex(ang, bott, innerradius, true);
        glTexCoord2f(0.8, 0.25);
        cyliVertex(ang + angleChange, bott, innerradius, true);
        cyliVertex(ang + angleChange, top, innerradius, true);
        glTexCoord2f(0.2, 0.25);
        cyliVertex(ang, top, innerradius, true);
    }
    glEnd();

    glPopMatrix();
}

void Dropper::topring(GLint angleChange, GLdouble innerradius, GLdouble outerradius)
{
    GLdouble top = 0.35;
    GLdouble bott = -0.54;
    glBindTexture(GL_TEXTURE_2D, textures[1]);
    glPushMatrix();
    glTranslatef(0, 0.65, 0);

    glBegin(GL_QUAD_STRIP);

    glNormal3f(0, 1, 0);
    glTexCoord2f(0.5, 0.5);

    for (int ang = 0; ang <= 360; ang += angleChange) //draw circle in chunks
    {
        glTexCoord2f(Sin(ang) / 2 + 0.5, Cos(ang) / 2 + 0.5);
        circleVertex(ang, 0, innerradius);
        glTexCoord2f(Sin(ang) / 2 + 0.5, Cos(ang) / 2 + 0.5);
        circleVertex(ang, 0, outerradius);
    }
    glEnd();

    glBegin(GL_QUAD_STRIP);

    glNormal3f(0, 1, 0);
    glTexCoord2f(0.5, 0.5);

    for (int ang = 360; ang >= 0; ang -= angleChange) //draw circle in chunks
    {
        glTexCoord2f(Sin(ang) / 2 + 0.5, Cos(ang) / 2 + 0.5);
        circleVertex(ang, top, innerradius);
        glTexCoord2f(Sin(ang) / 2 + 0.5, Cos(ang) / 2 + 0.5);
        circleVertex(ang, top, outerradius);
    }
    glEnd();

    //connect top circle to bottom circle
    glBegin(GL_QUADS);
    for (int ang = 0; ang <= 355; ang += angleChange)
    {
        glTexCoord2f(0.2, 0.25);
        cyliVertex(ang, top, outerradius);
        glTexCoord2f(0.8, 0.25);
        cyliVertex(ang + angleChange, top, outerradius);
        cyliVertex(ang + angleChange, 0, outerradius);
        glTexCoord2f(0.2, 0.25);
        cyliVertex(ang, 0, outerradius);
    }
    glEnd();

    glBegin(GL_QUADS);
    for (int ang = 355; ang >= 0; ang -= angleChange)
    {
        glTexCoord2f(0.2, 0.25);
        cyliVertex(ang, bott, innerradius, true);
        glTexCoord2f(0.8, 0.25);
        cyliVertex(ang + angleChange, bott, innerradius, true);
        cyliVertex(ang + angleChange, top, innerradius, true);
        glTexCoord2f(0.2, 0.25);
        cyliVertex(ang, top, innerradius, true);
    }
    glEnd();

    //add texture
    glTranslatef(0, 0.1, 0);
    glScalef(0.913785, 1, 0.913785);
    const int d = 5;
    int th, ph;

    //  Save transformation
    glPushMatrix();
    //  Offset and scale

    //  Latitude bands
    for (ph = -40; ph < 0; ph += d)
    {
        glBegin(GL_QUAD_STRIP);
        for (th = 360; th >= 0; th -= d)
        {
            glTexCoord2f((th + 0.0) / 360, (ph + 0.0) / -40);
            sphereVertex(th, ph);
            glTexCoord2f((th + 0.0) / 360, (ph + d + 0.0) / -40);
            sphereVertex(th, ph + d);
        }
        glEnd();
    }

    //  Undo transformations
    glPopMatrix();

    glPopMatrix();
}

void Dropper::gate(GLint angleChange, GLdouble radius)
{
    GLdouble lev = -0.85;
    glBindTexture(GL_TEXTURE_2D, textures[2]);
    glPushMatrix();

    glBegin(GL_TRIANGLE_FAN);

    glNormal3f(0, -1, 0);
    glTexCoord2f(0, 0.5);
    glVertex3f(0, lev - 0.05, 0); //set center point for top circle

    for (int ang = 0; ang <= 360; ang += angleChange) //draw circle in chunks
    {
        glTexCoord2f(0.5, 0.5);
        circleVertex(ang - angleChange, lev - 0.05, 0.8);
        glTexCoord2f(0, 0);
        circleVertex(ang, lev - 0.05, 0.8);
    }
    glEnd();

    glTranslatef(0, lev + 0.05, 0);
    glRotatef(180, 0, 0, 1);
    glBegin(GL_TRIANGLE_FAN);

    glNormal3f(0, -1, 0);
    glTexCoord2f(0, 0.5);
    glVertex3f(0, 0, 0); //set center point for top circle

    for (int ang = 0; ang <= 360; ang += angleChange) //draw circle in chunks
    {
        glTexCoord2f(0.5, 0.5);
        circleVertex(ang - angleChange, 0, 0.8);
        glTexCoord2f(0, 0);
        circleVertex(ang, 0, 0.8);
    }
    glEnd();

    glPopMatrix();
}

void Dropper::rods(GLint count)
{
    GLdouble angleChange = ((GLdouble)360) / count;
    GLdouble rad = 0.05;
    glBindTexture(GL_TEXTURE_2D, textures[3]);

    for (GLdouble ang = angleChange; ang <= 360; ang += angleChange)
    {
        glPushMatrix();
        glTranslatef(0.95 * Cos(ang),0,0.95 * Sin(ang));
        glBegin(GL_QUAD_STRIP);

        glNormal3f(0, 1, 0);
        glTexCoord2f(0.5, 0.5);

        for (int ang = 0; ang <= 360; ang += 5) //draw circle in chunks
        {
            glTexCoord2f(1,0.5);
            cyliVertex(ang, -0.7, rad);
            glTexCoord2f(0,0.5);
            cyliVertex(ang, 0.65, rad);
        }
        glEnd();
        glPopMatrix();
    }
}

void Dropper::DrawShape()
{
    float white[] = {1, 1, 1, 1};
    float black[] = {0, 0, 0, 1};
    float shiny = 1; // Shininess (value)
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shiny);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, white);
    glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, black);
    
    //  Save transformation
    glPushMatrix();

    glEnable(GL_TEXTURE_2D);

    bottomring(5, 0.7, 1);
    topring(5, 0.7, 1);
    gate(20, 0.8);
    rods(6);
    cylinder(5, 0.7, 1);

    glDisable(GL_TEXTURE_2D);
    //  Undo transformations
    glPopMatrix();
}