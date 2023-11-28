#include "CSCIx229.h"

void axesHelper(double length)
{
    const double len = length;  //  Length of axes
    glBegin(GL_LINES);

    glColor3f(1,0,0);
    glVertex3d(0.0,0.0,0.0);
    glVertex3d(len,0.0,0.0);
    glColor3f(0,1,0);
    glVertex3d(0.0,0.0,0.0);
    glVertex3d(0.0,len,0.0);
    glColor3f(0,0,1);
    glVertex3d(0.0,0.0,0.0);
    glVertex3d(0.0,0.0,len);
    glEnd();
    //  Label axes
    
    glColor3f(1,1,1);
    glRasterPos3d(len,0.0,0.0);
    Print("X");
    glRasterPos3d(0.0,len,0.0);
    Print("Y");
    glRasterPos3d(0.0,0.0,len);
    Print("Z");

}