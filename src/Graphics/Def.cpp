#include "Def.h"

void circleVertex(GLdouble ang)
{
   glNormal3f(0, 1, 0);
   glVertex3d(Cos(ang), 0, Sin(ang));
}

void circleVertex(GLdouble ang, GLdouble height)
{
   glNormal3f(0, height, 0);
   glVertex3d(Cos(ang), height, Sin(ang));
}

void circleVertex(GLdouble ang, GLdouble height, GLdouble rad)
{
   glNormal3f(0, height, 0);
   glVertex3d(Cos(ang) * rad, height, Sin(ang) * rad);
}

void ovalVertex(GLdouble ang, GLdouble width, GLdouble height)
{
   glNormal3f(0, 1, 0);
   glVertex3d(width * Cos(ang), height * Sin(ang), 0);
}

void cyliVertex(GLdouble ang, GLdouble height)
{
   glNormal3f(Cos(ang), 0, Sin(ang));
   glVertex3d(Cos(ang), height, Sin(ang));
}

void cyliVertex(GLdouble ang, GLdouble height, GLdouble rad)
{
   glNormal3f(Cos(ang), 0, Sin(ang));
   glVertex3d(Cos(ang) * rad, height, Sin(ang) * rad);
}

void cyliVertex(GLdouble ang, GLdouble height, GLdouble rad, bool invert)
{
   if (invert)
      glNormal3f(-Cos(ang), 0, -Sin(ang));
   else
      glNormal3f(Cos(ang), 0, Sin(ang));

   glVertex3d(Cos(ang) * rad, height, Sin(ang) * rad);
}

//borrowed from ex8
void sphereVertex(double th,double ph)
{
   glNormal3f(Sin(th)*Cos(ph) , Sin(ph) , Cos(th)*Cos(ph));
   glVertex3d(Sin(th)*Cos(ph) , Sin(ph) , Cos(th)*Cos(ph));
}

/*
 *  Draw a sphere (version 2) (from ex8)
 *     at (x,y,z)
 *     radius (r)
 */
void sphere(double x,double y,double z,double r)
{
   const int d=15;
   int th,ph;

   //  Save transformation
   glPushMatrix();
   //  Offset and scale
   glTranslated(x,y,z);
   glScaled(r,r,r);

   //  Latitude bands
   for (ph=-90;ph<90;ph+=d)
   {
      glBegin(GL_QUAD_STRIP);
      for (th=0;th<=360;th+=d)
      {
         sphereVertex(th,ph);
         sphereVertex(th,ph+d);
      }
      glEnd();
   }

   //  Undo transformations
   glPopMatrix();
}