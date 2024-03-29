#ifndef TEXTURE_HANDLER_H
#define TEXTURE_HANDLER_H

#include "includes.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <math.h>
#include <map>
#include <string>


namespace TextureHandler{
    unsigned int LoadTexture(std::string file, bool hasAlpha);
    unsigned int LoadBMPTexture(const char* file);
    unsigned int LoadBMPTexture32(const char* file);
}







#endif