#include "CSCIx229.h"


/**
 * Draw a cylinder at
 * double (x,y,z)
 * with base radius br, top radius tr, sector count sc,
 * and height h
 * emissive, and shiny
*/
void cylinder(double x,double y,double z,
              double br, double tr, double h, int sc,
              int emissive, float shiny, Color color)
{
    double angleStep = 2.0 * PI / sc;
    int i;

    // Material properties (if needed)
    if(emissive)
    {
        float mat_emission[] = {.6, .6, 0.1, 1.0};
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


    glPushMatrix();
    glTranslated(x, y, z);
    glColor3d(color.r, color.g, color.b);

    // Draw the bottom cap
    glBegin(GL_TRIANGLE_FAN);
    glNormal3d(0,-1,0);
    glTexCoord2f(0.5, 0.5);
    glVertex3d(0,0,0);
    for (i = 0; i <= sc; i++)
    {
        double angle = i * angleStep;
        glTexCoord2f(0.5 + 0.5 * cos(angle), 0.5 + 0.5 * sin(angle));
        glVertex3d(br * cos(angle), 0 , br * sin(angle));
    }
    glEnd();

    // Draw the top cap
    glBegin(GL_TRIANGLE_FAN);
    glNormal3d(0,1,0);
    glTexCoord2f(0.5, 0.5);
    glVertex3d(0,h,0);
    for (i = 0; i <= sc; i++)
    {
        double angle = i * angleStep;
        glTexCoord2f(0.5 + 0.5 * cos(angle), 0.5 + 0.5 * sin(angle));
        glVertex3d(br * cos(angle), h , br * sin(angle));
    }
    glEnd();

    // Draw the sides
    glBegin(GL_QUAD_STRIP);
    for (i = 0; i <= sc; i++)
    {
        double angle = i * angleStep;
        double nx = cos(angle);
        double nz = sin(angle);
        // normal
        glNormal3d(nx,0,nz);
        glTexCoord2f((double)i / sc, 0);
        // point on bottom face
        glTexCoord2f((double)i / sc, 0);
        glVertex3d(br * nx, 0, br * nz);
        // point on top face
        glTexCoord2f((double)i / sc, 1);
        glVertex3d(tr * nx, h, tr * nz);
    }
    glEnd();
    glPopMatrix();

}