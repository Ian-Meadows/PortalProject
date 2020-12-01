#include "companion.h"


Companion::Companion(Vector3D pos,  Vector3D scale, Vector3D rotation) :
 Object(pos, scale, rotation){
     std::vector<std::string> texture = {"Images/metalwall1_med.bmp", "Images/underground_wall_metal004d.bmp", "Images/woodpanel_002.bmp", "Images/metal_detail_01.bmp"};
     std::vector<bool> hasAlpha = {true,true,true,true};
        LoadTextures(texture, hasAlpha, "");
}

void Companion::cube()
{

    //  Cube
    glBindTexture(GL_TEXTURE_2D, textures[0]);
    glBegin(GL_QUADS);
    //  Front
    glNormal3f(0, 0, 1);
    glTexCoord2f(0, 0);
    glVertex3f(-1, -1, 1);
    glTexCoord2f(0, 1);
    glVertex3f(+1, -1, 1);
    glTexCoord2f(1, 1);
    glVertex3f(+1, +1, 1);
    glTexCoord2f(1, 0);
    glVertex3f(-1, +1, 1);
    //  Back
    glNormal3f(0, 0, -1);
    glTexCoord2f(0, 0);
    glVertex3f(+1, -1, -1);
    glTexCoord2f(0, 1);
    glVertex3f(-1, -1, -1);
    glTexCoord2f(1, 1);
    glVertex3f(-1, +1, -1);
    glTexCoord2f(1, 0);
    glVertex3f(+1, +1, -1);
    //  Right
    glNormal3f(1, 0, 0);
    glTexCoord2f(0, 0);
    glVertex3f(+1, -1, +1);
    glTexCoord2f(0, 1);
    glVertex3f(+1, -1, -1);
    glTexCoord2f(1, 1);
    glVertex3f(+1, +1, -1);
    glTexCoord2f(1, 0);
    glVertex3f(+1, +1, +1);
    //  Left
    glNormal3f(-1, 0, 0);
    glTexCoord2f(0, 0);
    glVertex3f(-1, -1, -1);
    glTexCoord2f(0, 1);
    glVertex3f(-1, -1, +1);
    glTexCoord2f(1, 1);
    glVertex3f(-1, +1, +1);
    glTexCoord2f(1, 0);
    glVertex3f(-1, +1, -1);
    //  Top
    glNormal3f(0, 1, 0);
    glTexCoord2f(0, 0);
    glVertex3f(-1, +1, +1);
    glTexCoord2f(0, 1);
    glVertex3f(+1, +1, +1);
    glTexCoord2f(1, 1);
    glVertex3f(+1, +1, -1);
    glTexCoord2f(1, 0);
    glVertex3f(-1, +1, -1);
    //  Bottom
    glNormal3f(0, -1, 0);
    glTexCoord2f(0, 0);
    glVertex3f(-1, -1, -1);
    glTexCoord2f(0, 1);
    glVertex3f(+1, -1, -1);
    glTexCoord2f(1, 1);
    glVertex3f(+1, -1, +1);
    glTexCoord2f(1, 0);
    glVertex3f(-1, -1, +1);
    //  End
    glEnd();
}

void Companion::sidePanel()
{

    glBindTexture(GL_TEXTURE_2D, textures[1]);
    glColor3f(1, 1, 1);
    glBegin(GL_QUADS);
    //corner
    glNormal3f(0, 1, 1);
    glTexCoord2f(0.9, 0.4);
    glVertex3f(+0.2, +1.06, +1.01);
    glTexCoord2f(0.1, 0.4);
    glVertex3f(-0.2, +1.06, +1.01);
    glTexCoord2f(0.1, 0.6);
    glVertex3f(-0.2, +1.01, +1.06);
    glTexCoord2f(0.9, 0.6);
    glVertex3f(+0.2, +1.01, +1.06);
    //side 1
    glNormal3f(0, +1.06, 0);
    glTexCoord2f(0.1, 0.4);
    glVertex3f(-0.2, +1.06, +1.01);
    glTexCoord2f(0.9, 0.4);
    glVertex3f(+0.2, +1.06, +1.01);
    glTexCoord2f(0.9, 0.1);
    glVertex3f(+0.2, +1.06, +0.85);
    glTexCoord2f(0.1, 0.1);
    glVertex3f(-0.2, +1.06, +0.85);

    glNormal3f(+0.2, 0, 0);
    glTexCoord2f(1, 0.1);
    glVertex3f(+0.2, +1, +0.85);
    glTexCoord2f(0.9, 0.1);
    glVertex3f(+0.2, +1.06, +0.85);
    glTexCoord2f(0.9, 0.4);
    glVertex3f(+0.2, +1.06, +1.01);
    glTexCoord2f(1, 0.4);
    glVertex3f(+0.2, +1, +1.01);

    glNormal3f(-0.2, 0, 0);
    glTexCoord2f(0, 0.1);
    glVertex3f(-0.2, +1, +0.85);
    glTexCoord2f(0, 0.4);
    glVertex3f(-0.2, +1, +1.01);
    glTexCoord2f(0.1, 0.4);
    glVertex3f(-0.2, +1.06, +1.01);
    glTexCoord2f(0.1, 0.1);
    glVertex3f(-0.2, +1.06, +0.85);

    glNormal3f(0, 0, -0.85);
    glTexCoord2f(0.1, 0);
    glVertex3f(-0.2, +1, +0.85);
    glTexCoord2f(0.1, 0.1);
    glVertex3f(-0.2, +1.06, +0.85);
    glTexCoord2f(0.9, 0.1);
    glVertex3f(+0.2, +1.06, +0.85);
    glTexCoord2f(0.9, 0);
    glVertex3f(+0.2, +1, +0.85);
    //side 2
    glNormal3f(0, 0, +1.06);
    glTexCoord2f(0.9, 0.9);
    glVertex3f(+0.2, +0.85, +1.06);
    glTexCoord2f(0.9, 0.6);
    glVertex3f(+0.2, +1.01, +1.06);
    glTexCoord2f(0.1, 0.6);
    glVertex3f(-0.2, +1.01, +1.06);
    glTexCoord2f(0.1, 0.9);
    glVertex3f(-0.2, +0.85, +1.06);

    glNormal3f(-0.2, 0, 0);
    glTexCoord2f(0.1, 0.6);
    glVertex3f(-0.2, +1.01, +1.06);
    glTexCoord2f(0, 0.6);
    glVertex3f(-0.2, +1.01, +1);
    glTexCoord2f(0, 0.9);
    glVertex3f(-0.2, +0.85, +1);
    glTexCoord2f(0.1, 0.9);
    glVertex3f(-0.2, +0.85, +1.06);

    glNormal3f(+0.2, 0, 0);
    glTexCoord2f(0.9, 0.6);
    glVertex3f(+0.2, +1.01, +1.06);
    glTexCoord2f(0.9, 0.9);
    glVertex3f(+0.2, +0.85, +1.06);
    glTexCoord2f(1, 0.9);
    glVertex3f(+0.2, +0.85, +1);
    glTexCoord2f(1, 0.6);
    glVertex3f(+0.2, +1.01, +1);

    glNormal3f(0, -0.85, 0);
    glTexCoord2f(0.9, 0.9);
    glVertex3f(+0.2, +0.85, +1.06);
    glTexCoord2f(0.1, 0.9);
    glVertex3f(-0.2, +0.85, +1.06);
    glTexCoord2f(0.1, 1);
    glVertex3f(-0.2, +0.85, +1);
    glTexCoord2f(0.9, 1);
    glVertex3f(+0.2, +0.85, +1);

    glEnd();

    //seal the corner with triangles
    glBegin(GL_TRIANGLES);
    glNormal3f(+0.2, 0, 0);
    glTexCoord2f(0.9, 0.4);
    glVertex3f(+0.2, +1.06, +1.01);
    glTexCoord2f(0.9, 0.6);
    glVertex3f(+0.2, +1.01, +1.06);
    glTexCoord2f(0.991, 0.4);
    glVertex3f(+0.2, +1.01, +1.01);

    glNormal3f(-0.2, 0, 0);
    glTexCoord2f(0.1, 0.4);
    glVertex3f(-0.2, +1.06, +1.01);
    glTexCoord2f(0.009, 0.4);
    glVertex3f(-0.2, +1.01, +1.01);
    glTexCoord2f(0.1, 0.6);
    glVertex3f(-0.2, +1.01, +1.06);

    glEnd();
}

void Companion::cornerPanel()
{
    glBindTexture(GL_TEXTURE_2D, textures[1]);
    glColor3f(1, 1, 1);
    glBegin(GL_TRIANGLES);
    //corner
    glNormal3f(1, 1, 1);
    glTexCoord2f(0.3, 0.3);
    glVertex3f(+1.06, +1.01, +1.01);
    glTexCoord2f(0.3, 0.6);
    glVertex3f(+1.01, +1.06, +1.01);
    glTexCoord2f(0.6, 0.3);
    glVertex3f(+1.01, +1.01, +1.06);

    glEnd();

    glBegin(GL_QUADS);
    //strips
    
    glNormal3f(0, 1, 1);
    glTexCoord2f(0.1, 0.1);
    glVertex3f(+0.3, +1.01, +1.06);
    glTexCoord2f(0.9, 0.1);
    glVertex3f(+1.01, +1.01, +1.06);
    glTexCoord2f(0.9, 0.9);
    glVertex3f(+1.01, +1.06, +1.01);
    glTexCoord2f(0.1, 0.9);
    glVertex3f(+0.3, +1.06, +1.01);

    glNormal3f(1, 0, 1);
    glTexCoord2f(0.9, 0.9);
    glVertex3f(+1.06, +1.01, +1.01);
    glTexCoord2f(0.9, 0.1);
    glVertex3f(+1.01, +1.01, +1.06);
    glTexCoord2f(0.1, 0.1);
    glVertex3f(+1.01, +0.3, +1.06);
    glTexCoord2f(0.1, 0.9);
    glVertex3f(+1.06, +0.3, +1.01);


    glNormal3f(1, 1, 0);
    glTexCoord2f(0.9, 0.9);
    glVertex3f(+1.01, +1.06, +1.01);
    glTexCoord2f(0.9, 0.1);
    glVertex3f(+1.06, +1.01, +1.01);
    glTexCoord2f(0.1, 0.1);
    glVertex3f(+1.06, +1.01, +0.3);
    glTexCoord2f(0.1, 0.9);
    glVertex3f(+1.01, +1.06, +0.3);
    glEnd(); 

    
    //strip end-caps
    glBegin(GL_TRIANGLES);
    glNormal3f(-0.3, 0, 0);
    glTexCoord2f(0.3, 0.3);
    glVertex3f(+0.3, +1.01, +1.06);
    glTexCoord2f(0.3, 0.6);
    glVertex3f(+0.3, +1.06, +1.01);
    glTexCoord2f(0.6, 0.3);
    glVertex3f(+0.3, +1.00, +1.00);

    glNormal3f(0, -0.3, 0);
    glTexCoord2f(0.3, 0.6);
    glVertex3f(+1.06, +0.3, +1.01);
    glTexCoord2f(0.3, 0.3);
    glVertex3f(+1.01, +0.3, +1.06);
    glTexCoord2f(0.6, 0.3);
    glVertex3f(+1.00, +0.3, +1.00);

    glNormal3f(0, 0, -0.3);
    glTexCoord2f(0.3, 0.6);
    glVertex3f(+1.01, +1.06, +0.3);
    glTexCoord2f(0.3, 0.3);
    glVertex3f(+1.06, +1.01, +0.3);
    glTexCoord2f(0.6, 0.3);
    glVertex3f(+1.00, +1.00, +0.3);

    glEnd();

    glBegin(GL_QUADS);
    //inner cover pieces
    glNormal3f(-1, -1, 0);
    glTexCoord2f(0.7, 0.7);
    glVertex3f(+1.01, +0.3, +1.00);
    glTexCoord2f(0.3, 0.7);
    glVertex3f(+1.01, +0.3, +1.06);
    glTexCoord2f(0.3, 0.3);
    glVertex3f(+0.3, +1.01, +1.06);
    glTexCoord2f(0.7, 0.3);
    glVertex3f(+0.3, +1.01, +1.00);

    glNormal3f(0, -1, -1);
    glTexCoord2f(0.7, 0.7);
    glVertex3f(+1.00, +1.01, +0.3);
    glTexCoord2f(0.3, 0.7);
    glVertex3f(+1.06, +1.01, +0.3);
    glTexCoord2f(0.3, 0.3);
    glVertex3f(+1.06, +0.3, +1.01);
    glTexCoord2f(0.7, 0.3);
    glVertex3f(+1.00, +0.3, +1.01);

    glNormal3f(-1, 0, -1);
    glTexCoord2f(0.3, 0.3);
    glVertex3f(+0.3, +1.06, +1.01);
    glTexCoord2f(0.3, 0.7);
    glVertex3f(+1.01, +1.06, +0.3);
    glTexCoord2f(0.7, 0.7);
    glVertex3f(+1.01, +1.00, +0.3);
    glTexCoord2f(0.7, 0.3);
    glVertex3f(+0.3, +1.00, +1.01);

    glEnd();

    glBindTexture(GL_TEXTURE_2D, textures[2]);

    glBegin(GL_TRIANGLES);
    //corner plates
    glNormal3f(0, 0, +1.06);
    glTexCoord2f(0.1, 0.1);
    glVertex3f(+0.3, +1.01, +1.06);
    glTexCoord2f(0, 0.5);
    glVertex3f(+1.01, +0.3, +1.06);
    glTexCoord2f(0.5, 0);
    glVertex3f(+1.01, +1.01, +1.06);

    glNormal3f(+1.06, 0, 0);
    glTexCoord2f(0.1, 0.1);
    glVertex3f(+1.06, +0.3, +1.01);
    glTexCoord2f(0, 0.5);
    glVertex3f(+1.06, +1.01, +0.3);
    glTexCoord2f(0.5, 0);
    glVertex3f(+1.06, +1.01, +1.01);

    glNormal3f(0, +1.06, 0);
    glTexCoord2f(0, 0.5);
    glVertex3f(+1.01, +1.06, +0.3);
    glTexCoord2f(0.1, 0.1);
    glVertex3f(+0.3, +1.06, +1.01);
    glTexCoord2f(0.5, 0);
    glVertex3f(+1.01, +1.06, +1.01);

    glEnd();
}

void Companion::cylinder(GLint angleChange, GLdouble radius, GLdouble height)
{
    glMateriali(GL_FRONT_AND_BACK, GL_SHININESS, 128);
    glBindTexture(GL_TEXTURE_2D, textures[3]);
    glPushMatrix();
    glScaled(radius, height, radius);

    glBegin(GL_TRIANGLE_FAN);

    glNormal3f(0, 1, 0);
    glTexCoord2f(0.5, 0.5);
    glVertex3f(0, 1, 0); //set center point for top circle

    for (int ang = 0; ang <= 360; ang += angleChange) //draw circle in chunks
    {
        glTexCoord2f(Sin(ang) / 2 + 0.5, Cos(ang) / 2 + 0.5);
        circleVertex(ang, 1);
        glTexCoord2f(Sin(ang - angleChange) / 2 + 0.5, Cos(ang - angleChange) / 2 + 0.5);
        circleVertex(ang - angleChange, 1);
    }
    glEnd();

    glBegin(GL_TRIANGLE_FAN);

    glNormal3f(0, -1, 0);
    glTexCoord2f(0.5, 0.5);
    glVertex3f(0, -1, 0); //set center point for top circle

    for (int ang = 0; ang <= 360; ang += angleChange) //draw circle in chunks
    {
        glTexCoord2f(Sin(ang) / 2 + 0.5, Cos(ang) / 2 + 0.5);
        circleVertex(ang, -1);
        glTexCoord2f(Sin(ang + angleChange) / 2 + 0.5, Cos(ang + angleChange) / 2 + 0.5);
        circleVertex(ang + angleChange, -1);
    }
    glEnd();

    //connect top circle to bottom circle
    glBegin(GL_QUADS);
    for (int ang = 0; ang <= 360; ang += angleChange)
    {
        glTexCoord2f(Sin(ang) / 2 + 0.5, Cos(ang) / 2 + 0.5);
        cyliVertex(ang, 1);
        glTexCoord2f(Sin(ang + angleChange) / 2 + 0.5, Cos(ang + angleChange) / 2 + 0.5);
        cyliVertex(ang + angleChange, 1);
        cyliVertex(ang + angleChange, -1);
        glTexCoord2f(Sin(ang) / 2 + 0.5, Cos(ang) / 2 + 0.5);
        cyliVertex(ang, -1);
    }
    glEnd();

    glPopMatrix();
    glMateriali(GL_FRONT_AND_BACK, GL_SHININESS, 0);
}

void Companion::DrawShape()
{

    //  Save transformation
    glPushMatrix();

    glEnable(GL_TEXTURE_2D);

    glColor3f(0.427, 0.522, 0.569);

    cube();

    //side panels (need 12)

    //top
    glPushMatrix();
    sidePanel();
    glRotated(90, 0, 1, 0);
    sidePanel();
    glRotated(90, 0, 1, 0);
    sidePanel();
    glRotated(90, 0, 1, 0);
    sidePanel();
    glPopMatrix();

    //bottom
    glPushMatrix();
    glRotated(90, 1, 0, 0);
    sidePanel();
    glRotated(90, 0, 0, 1);
    sidePanel();
    glRotated(90, 0, 0, 1);
    sidePanel();
    glRotated(90, 0, 0, 1);
    sidePanel();
    glPopMatrix();

    //middle
    glPushMatrix();
    glRotated(90, 0, 0, 1);
    sidePanel();
    glRotated(90, 1, 0, 0);
    sidePanel();
    glRotated(90, 1, 0, 0);
    sidePanel();
    glRotated(90, 1, 0, 0);
    sidePanel();
    glPopMatrix();

    //corners (8)

    //top
    glPushMatrix();
    cornerPanel();
    glRotated(90, 0, 1, 0);
    cornerPanel();
    glRotated(90, 0, 1, 0);
    cornerPanel();
    glRotated(90, 0, 1, 0);
    cornerPanel();
    glPopMatrix();

    //bottom
    glPushMatrix();
    glRotated(180, 1, 0, 0);
    cornerPanel();
    glRotated(90, 0, 1, 0);
    cornerPanel();
    glRotated(90, 0, 1, 0);
    cornerPanel();
    glRotated(90, 0, 1, 0);
    cornerPanel();
    glPopMatrix();

    //fun with cylinders (the ones in the center of each side)
    glColor3f(1, 1, 1);

    glPushMatrix();

    glTranslated(0, 1.025, 0);
    glColor3f(1, 1, 1);
    cylinder(5, 0.5, 0.025);

    glPopMatrix();
    glPushMatrix();

    glRotated(90, 1, 0, 0);
    glTranslated(0, 1.025, 0);
    glColor3f(0.72549, 0, 0);
    cylinder(5, 0.5, 0.025);

    glPopMatrix();
    glPushMatrix();

    glRotated(180, 1, 0, 0);
    glTranslated(0, 1.025, 0);
    glColor3f(1, 0.83529, 0);
    cylinder(5, 0.5, 0.025);

    glPopMatrix();
    glPushMatrix();

    glRotated(270, 1, 0, 0);
    glTranslated(0, 1.025, 0);
    glColor3f(1, 0.349, 0);
    cylinder(5, 0.5, 0.025);

    glPopMatrix();
    glPushMatrix();

    glRotated(90, 0, 0, 1);
    glTranslated(0, 1.025, 0);
    glColor3f(0, 0.2705, 0.6784);
    cylinder(5, 0.5, 0.025);

    glPopMatrix();
    glPushMatrix();

    glRotated(270, 0, 0, 1);
    glTranslated(0, 1.025, 0);
    glColor3f(0, 0.6078, 0.2823);
    cylinder(5, 0.5, 0.025);

    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
    //  Undo transformations
    glPopMatrix();
}