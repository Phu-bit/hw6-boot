#include "CSCIx229.h"

/*
 *  Draw vertex in polar coordinates with normal
 */
static void Vertex(double th,double ph)
{
   double x = Sin(th)*Cos(ph);
   double y = Cos(th)*Cos(ph);
   double z =         Sin(ph);
   //  For a sphere at the origin, the position
   //  and normal vectors are the same
   glNormal3d(x,y,z);
   glVertex3d(x,y,z);
}

/*
 *  Draw a ball
 *     at (x,y,z)
 *     radius (r)
 *     emission, shiny, inc
 */
void ball(double x,double y,double z,double r, int emission, float shiny, int inc)
{
   //  Save transformation
   glPushMatrix();
   //  Offset, scale and rotate
   glTranslated(x,y,z);
   glScaled(r,r,r);
   //  White ball with yellow specular
   float yellow[]   = {1.0,1.0,0.0,1.0};
   float Emission[] = {0.0,0.0,0.01*emission,1.0};
   glColor3f(1,1,1);
   glMaterialf(GL_FRONT,GL_SHININESS,shiny);
   glMaterialfv(GL_FRONT,GL_SPECULAR,yellow);
   glMaterialfv(GL_FRONT,GL_EMISSION,Emission);
   //  Bands of latitude
   for (int ph=-90;ph<90;ph+=inc)
   {
      glBegin(GL_QUAD_STRIP);
      for (int th=0;th<=360;th+=2*inc)
      {
         Vertex(th,ph);
         Vertex(th,ph+inc);
      }
      glEnd();
   }
   //  Undo transofrmations
   glPopMatrix();
}

void hemisphere(double x,double y,double z,double r,
                int emission, float shiny, Color color)
{
   //  Save transformation
   glPushMatrix();
   //  Offset and scale
   glTranslated(x,y,z);
   glRotated(-90,0,0,1);
   glScaled(r,r,r);

    // Material properties (if needed)
    if(emission)
    {
        float mat_emission[] = {.6, .6, 0.1 * emission , 1.0};
        glMaterialfv(GL_FRONT, GL_EMISSION,mat_emission);
    }
    if(shiny > 0)
    {
        float yellow[]   = {1.0,1.0,0.0,1.0};

        //float mat_specular[] = {1.0, 1.0, 1.0, 1.0};
        float mat_shininess[] = {shiny};
        glMaterialfv(GL_FRONT,GL_SPECULAR,yellow);
        glMaterialfv(GL_FRONT,GL_SHININESS,mat_shininess);
    }

   float matColor[] = {color.r, color.g, color.b, 1.0};
   glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE,matColor);
   glColor3d(color.r, color.g, color.b);

      for (int ph=-90;ph<90;ph+=10)
   {
      glBegin(GL_QUAD_STRIP);
      for (int th=0;th<=180;th+=2*10)
      {
         Vertex(th,ph);
         Vertex(th,ph+10);
      }
      glEnd();
   }


   // Undo transformations
   glPopMatrix();
}
