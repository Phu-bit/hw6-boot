#include "CSCIx229.h"

typedef struct {float x,y,z;} vtx;
typedef struct {int A,B,C;} tri;
#define n 500
vtx is[n];

/*
 *  Icosahedron data
 */
const int N=20;
//  Triangle index list
const tri idx[] =
   {
      { 2, 1, 0}, { 3, 2, 0}, { 4, 3, 0}, { 5, 4, 0}, { 1, 5, 0},
      {11, 6, 7}, {11, 7, 8}, {11, 8, 9}, {11, 9,10}, {11,10, 6},
      { 1, 2, 6}, { 2, 3, 7}, { 3, 4, 8}, { 4, 5, 9}, { 5, 1,10},
      { 2, 7, 6}, { 3, 8, 7}, { 4, 9, 8}, { 5,10, 9}, { 1, 6,10}
   };
//  Vertex coordinates
const vtx xyz[] =
   {
      { 0.000, 0.000, 1.000}, { 0.894, 0.000, 0.447}, { 0.276, 0.851, 0.447},
      {-0.724, 0.526, 0.447}, {-0.724,-0.526, 0.447}, { 0.276,-0.851, 0.447},
      { 0.724, 0.526,-0.447}, {-0.276, 0.851,-0.447}, {-0.894, 0.000,-0.447},
      {-0.276,-0.851,-0.447}, { 0.724,-0.526,-0.447}, { 0.000, 0.000,-1.000}
   };
/*
 * Draw triangle
 */
static void triangle(vtx A,vtx B,vtx C)
{
   //  Planar vector 0
   float dx0 = A.x-B.x;
   float dy0 = A.y-B.y;
   float dz0 = A.z-B.z;
   //  Planar vector 1
   float dx1 = C.x-A.x;
   float dy1 = C.y-A.y;
   float dz1 = C.z-A.z;
   //  Normal
   float Nx = dy0*dz1 - dy1*dz0;
   float Ny = dz0*dx1 - dz1*dx0;
   float Nz = dx0*dy1 - dx1*dy0;
   //  Draw triangle
   glNormal3f(Nx,Ny,Nz);
   glBegin(GL_TRIANGLES);
   glVertex3f(A.x,A.y,A.z);
   glVertex3f(B.x,B.y,B.z);
   glVertex3f(C.x,C.y,C.z);
   glEnd();
}

/*
 *  Draw icosahedron
 *     at (x,y,z)
 *     size  s
 *     rotated th about the x axis
 */
void icosahedron(float x,float y,float z,float s,float th, float shiny)
{
   //  Purple icosahedron with white specular and no emission
   float black[]  = {0.0,0.0,0.0,1.0};
   float purple[] = {1.0,0.0,0.5,1.0};
   float white[]  = {1.0,1.0,1.0,1.0};
   glColor4fv(purple);
   glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,black);
   glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE,purple);
   glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,white);
   glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,shiny);
   //  Draw icosahedron
   glPushMatrix();
   glTranslatef(x,y,z);
   glScalef(s,s,s);
   glRotatef(th,0,1,0);
   glRotatef(-90,1,0,0);
   for (int i=0;i<N;i++)
      triangle(xyz[idx[i].A],xyz[idx[i].B],xyz[idx[i].C]);
   glPopMatrix();
}


/*
 *  Draw sphere approximated by the inscribed icosahedron
 *     at (x,y,z)
 *     size  s
 *  KILLER FACT:  glNormal==glVertex because because the icosasphere 
 *    is a low poly count representation the circumscribed sphere.
 *    Doing this for any other object is almost certainly wrong.
 *    If you change any of the vertex values, the normals will be wrong.
 *    DO NOT USE THIS OBJECT FOR ANYTING OTHER THAN A SMALL SPHERE!!!
 */
void icosasphere(float x,float y,float z,float s, float shiny)
{
   //  Yellow with white specular and no emission
   float black[]  = {0.0,0.0,0.0,1.0};
   float yellow[] = {1.0,1.0,0.0,1.0};
   float white[]  = {1.0,1.0,1.0,1.0};
   glColor4fv(yellow);
   glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,black);
   glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE,yellow);
   glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,white);
   glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,shiny);
   //  Set transforms
   glPushMatrix();
   glTranslatef(x,y,z);
   glScalef(s,s,s);
   glRotatef(-90,1,0,0);
   //  Since this is a sphere the vertex and normal values are the same
   glVertexPointer(3,GL_FLOAT,0,xyz);
   glEnableClientState(GL_VERTEX_ARRAY);
   glNormalPointer(GL_FLOAT,0,xyz);
   glEnableClientState(GL_NORMAL_ARRAY);
   //  Draw icosahedron (3*N is number of vertices)
   glDrawElements(GL_TRIANGLES,3*N,GL_UNSIGNED_INT,idx);
   //  Reset state
   glDisableClientState(GL_VERTEX_ARRAY);
   glDisableClientState(GL_NORMAL_ARRAY);
   glPopMatrix();
}
