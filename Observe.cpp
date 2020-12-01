#include "Observe.h"



Observe::Observe(Vector3D pos, Vector3D scale, Vector3D rotation) : Object(pos, scale, rotation)
{
    std::vector<std::string> texture = {"Images/white_wall_tile001a.bmp", "Images/metalwall1_lrg.bmp"};
    std::vector<bool> hasAlpha = {true, true};
    LoadTextures(texture, hasAlpha);
}

void Observe::cylinder(GLint angleChange, GLdouble radius, GLdouble height)
{
    glMateriali(GL_FRONT_AND_BACK, GL_SHININESS, 128);
    glPushMatrix();
    glScaled(radius, height, radius);

    glBegin(GL_TRIANGLE_FAN);

    glNormal3f(0, 1, 0);
    glTexCoord2f(0.5, 0.5);
    glVertex3f(0, 1, 0); //set center point for top circle

    for (int ang = 0; ang <= 360; ang += angleChange) //draw circle in chunks
    {
        glTexCoord2f(Sin(ang) / 3 + 0.5, Cos(ang) / 3 + 0.5);
        circleVertex(ang, 1);
        glTexCoord2f(Sin(ang - angleChange) / 3 + 0.5, Cos(ang - angleChange) / 3 + 0.5);
        circleVertex(ang - angleChange, 1);
    }
    glEnd();

    glBegin(GL_TRIANGLE_FAN);

    glNormal3f(0, -1, 0);
    glTexCoord2f(0.5, 0.5);
    glVertex3f(0, -1, 0); //set center point for top circle

    for (int ang = 0; ang <= 360; ang += angleChange) //draw circle in chunks
    {
        glTexCoord2f(Sin(ang) / 3 + 0.5, Cos(ang) / 3 + 0.5);
        circleVertex(ang, -1);
        glTexCoord2f(Sin(ang + angleChange) / 3 + 0.5, Cos(ang + angleChange) / 3 + 0.5);
        circleVertex(ang + angleChange, -1);
    }
    glEnd();

    //connect top circle to bottom circle
    glBegin(GL_QUADS);
    for (int ang = 0; ang <= 360; ang += angleChange)
    {
        glTexCoord2f(Sin(ang) / 3 + 0.5, Cos(ang) / 3 + 0.5);
        cyliVertex(ang, 1);
        glTexCoord2f(Sin(ang + angleChange) / 3 + 0.5, Cos(ang + angleChange) / 3 + 0.5);
        cyliVertex(ang + angleChange, 1);
        cyliVertex(ang + angleChange, -1);
        glTexCoord2f(Sin(ang) / 3 + 0.5, Cos(ang) / 3 + 0.5);
        cyliVertex(ang, -1);
    }
    glEnd();

    glPopMatrix();
    glMateriali(GL_FRONT_AND_BACK, GL_SHININESS, 0);
}

void Observe::cam(GLint angleChange, GLdouble radius, GLdouble height)
{
    glBindTexture(GL_TEXTURE_2D, textures[0]);
    glMateriali(GL_FRONT_AND_BACK, GL_SHININESS, 128);
    glPushMatrix();
    glScaled(radius, height, radius);

    glBegin(GL_TRIANGLE_FAN);

    glNormal3f(0, 1, 0);
    glTexCoord2f(0.5, 0.5);
    glVertex3f(0, 1, 0); //set center point for top circle

    for (int ang = 0; ang <= 360; ang += angleChange) //draw circle in chunks
    {
        glTexCoord2f(Sin(ang) / 3 + 0.5, Cos(ang) / 3 + 0.5);
        circleVertex(ang, 1);
        glTexCoord2f(Sin(ang - angleChange) / 3 + 0.5, Cos(ang - angleChange) / 3 + 0.5);
        circleVertex(ang - angleChange, 1);
    }
    glEnd();

    glBegin(GL_TRIANGLE_FAN);

    glNormal3f(0, -1, 0);
    glTexCoord2f(0.5, 0.5);
    glVertex3f(0, -1, 0); //set center point for top circle

    for (int ang = 0; ang <= 360; ang += angleChange) //draw circle in chunks
    {
        glTexCoord2f(Sin(ang) / 3 + 0.5, Cos(ang) / 3 + 0.5);
        circleVertex(ang, -1);
        glTexCoord2f(Sin(ang + angleChange) / 3 + 0.5, Cos(ang + angleChange) / 3 + 0.5);
        circleVertex(ang + angleChange, -1);
    }
    glEnd();

    //connect top circle to bottom circle
    glBegin(GL_QUADS);
    for (int ang = 0; ang <= 360; ang += angleChange)
    {
        glTexCoord2f(Sin(ang) / 3 + 0.5, Cos(ang) / 3 + 0.5);
        cyliVertex(ang, 1);
        glTexCoord2f(Sin(ang + angleChange) / 3 + 0.5, Cos(ang + angleChange) / 3 + 0.5);
        cyliVertex(ang + angleChange, 1);
        cyliVertex(ang + angleChange, -1);
        glTexCoord2f(Sin(ang) / 3 + 0.5, Cos(ang) / 3 + 0.5);
        cyliVertex(ang, -1);
    }
    glEnd();

    glPushMatrix();
    {
        glScalef(0.8, 1.1, 0.8);
        glBindTexture(GL_TEXTURE_2D, textures[1]);

        glBegin(GL_TRIANGLE_FAN);

        glNormal3f(0, 1, 0);
        glTexCoord2f(0.5, 0.5);
        glVertex3f(0, 1, 0); //set center point for top circle

        for (int ang = 0; ang <= 360; ang += angleChange) //draw circle in chunks
        {
            glTexCoord2f(Sin(ang) / 3 + 0.5, Cos(ang) / 3 + 0.5);
            circleVertex(ang, 1);
            glTexCoord2f(Sin(ang - angleChange) / 3 + 0.5, Cos(ang - angleChange) / 3 + 0.5);
            circleVertex(ang - angleChange, 1);
        }
        glEnd();

        glBegin(GL_QUADS);
        for (int ang = 0; ang <= 360; ang += angleChange)
        {
            glTexCoord2f(Sin(ang) / 3 + 0.5, Cos(ang) / 3 + 0.5);
            cyliVertex(ang, 1);
            glTexCoord2f(Sin(ang + angleChange) / 3 + 0.5, Cos(ang + angleChange) / 3 + 0.5);
            cyliVertex(ang + angleChange, 1);
            cyliVertex(ang + angleChange, 0.8);
            glTexCoord2f(Sin(ang) / 3 + 0.5, Cos(ang) / 3 + 0.5);
            cyliVertex(ang, 0.8);
        }
        glEnd();
    }
    glPopMatrix();

    glPopMatrix();
    glMateriali(GL_FRONT_AND_BACK, GL_SHININESS, 0);
}

void Observe::DrawShape()
{

    glEnable(GL_TEXTURE_2D);
    //  Save transformation
    glPushMatrix();
    {
        glBindTexture(GL_TEXTURE_2D, textures[1]);

        //base
        glPushMatrix();
        {
            glEnable(GL_POLYGON_OFFSET_FILL);
            glPolygonOffset(-3, -3);
            glRotatef(90, 1, 0, 0);
            glBegin(GL_TRIANGLE_FAN);
            int angleChange = 5;

            glNormal3f(0, 1, 0);
            glTexCoord2f(0.5, 0.5);
            glVertex3f(0, 1, 0); //set center point for top circle

            for (int ang = 0; ang <= 360; ang += angleChange) //draw circle in chunks
            {
                glTexCoord2f(Sin(ang - angleChange) / 3 + 0.5, Cos(ang - angleChange) / 3 + 0.5);
                circleVertex(ang - angleChange, 1);
                glTexCoord2f(Sin(ang) / 3 + 0.5, Cos(ang) / 3 + 0.5);
                circleVertex(ang, 1);
            }
            glEnd();
            glPolygonOffset(0, 0);
            glDisable(GL_POLYGON_OFFSET_FILL);
        }
        glPopMatrix();
        //extendo
        glPushMatrix();
        {
            glPushMatrix();
            {
                glTranslatef(0, 0.5, 0.7);
                glRotatef(-37, 1, 0, 0);
                cylinder(5, 0.06, 0.5);
            }
            glPopMatrix();
            glPushMatrix();
            {
                glTranslatef(0, 0.53, 0.1);
                glRotatef(45, 1, 0, 0);
                cylinder(5, 0.04, 0.5);
            }
            glPopMatrix();
        }
        glPopMatrix();
        //cam
        glPushMatrix();
        {
            glTranslatef(0, 0, -0.15);
            glRotatef(-18, 0, 1, 0);
            glRotatef(101, 0, 0, 1);
            cam(5, 0.3, 0.5);
        }
        glPopMatrix();
    }
    glPopMatrix();

    glDisable(GL_TEXTURE_2D);
}