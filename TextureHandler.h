#ifndef TEXTURE_HANDLER_H
#define TEXTURE_HANDLER_H

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <math.h>


#define GL_GLEXT_PROTOTYPES
#include <GL/glut.h>


namespace TextureHandler{
    unsigned int LoadBMPTexture(const char* file);
    unsigned int LoadBMPTexture32(const char* file);
}







#endif