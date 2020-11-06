#include "Portal.h"

Portal::Portal(Vector3D pos, Vector3D scale, Vector3D rotation) : Object(pos, scale, rotation)
{
    //implement framebuffer and texture for portal
    glGenFramebuffers(1, &fbo);
    glBindFramebuffer(GL_FRAMEBUFFER, fbo);

    textures = new unsigned int[1];
    glGenTextures(1, &textures[0]);
    glBindTexture(GL_TEXTURE_2D, textures[0]);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 1440, 1440, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBindTexture(GL_TEXTURE_2D, 0);

    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, textures[0], 0);

    glGenRenderbuffers(1, &rbo);
    glBindRenderbuffer(GL_RENDERBUFFER, rbo);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, 1440, 1440);
    glBindRenderbuffer(GL_RENDERBUFFER, 0);

    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo);

    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
    {
        std::cout << "ERROR SETTING UP THE FRAMEBUFFER!" << std::endl;
    }
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Portal::setOtherPortal(Portal *other)
{
    otherPortal = other;
}

void Portal::enablePortalDrawing(Vector3D &pos, Vector3D &rot)
{
    glBindFramebuffer(GL_FRAMEBUFFER,fbo);
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    pos = otherPortal->getPosition();
    rot = otherPortal->getRotation();
}

Portal::~Portal()
{
    glDeleteFramebuffers(1,&fbo);
    glDeleteRenderbuffers(1,&rbo);
    //glDeleteTextures(1,&textures[0]);
}

void Portal::DrawShape()
{

    int rep = 1;

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
