#include "Print.h"
//
//  Convenience routine to output raster text
//  Use VARARGS to make this more flexible
//

//
//  Output text as bitmaps
//
#define LEN 8192  //  Maximum length of text string
void Print(const char* format , ...)
{
   char    buf[LEN];
   va_list args;
   //  Turn the parameters into a character string
   va_start(args,format);
   vsnprintf(buf,LEN,format,args);
   va_end(args);
   //  Setup font as display lists on first use
   if (!font)
   {
      int i;
      glPixelStorei(GL_UNPACK_ALIGNMENT,1);
      font = glGenLists(256);
      for (i=0;i<256;i++)
      {
         glNewList(font+i,GL_COMPILE);
         glBitmap(8,14,0.0,0.0,9.0,0.0,letters[i]);
         glEndList();
      }
   }
   //  Display the characters at the current raster position
   glListBase(font);
   glCallLists(strlen(buf),GL_UNSIGNED_BYTE,(GLubyte *)buf);
}

