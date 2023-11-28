#ifndef CSCIx229
#define CSCIx229

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <math.h>

// GLEW _MUST_ be included first
#ifdef USEGLEW
#include <GL/glew.h>
#endif
//  Get all GL prototypes
#define GL_GLEXT_PROTOTYPES
//  Select SDL, SDL2, GLFW or GLUT
#if defined(SDL2)
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#elif defined(SDL)
#include <SDL/SDL.h>
#include <SDL/SDL_mixer.h>
#elif defined(GLFW)
#include <GLFW/glfw3.h>
#elif defined(__APPLE__)
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
//  Make sure GLU and GL are included
#ifdef __APPLE__
#include <OpenGL/glu.h>
#include <OpenGL/gl.h>
// Tell Xcode IDE to not gripe about OpenGL deprecation
#pragma clang diagnostic ignored "-Wdeprecated-declarations"
#else
#include <GL/glu.h>
#include <GL/gl.h>
#endif
//  Default resolution
//  For Retina displays compile with -DRES=2
#ifndef RES
#define RES 1
#endif

//  cos and sin in degrees
#define Cos(th) cos(3.14159265/180*(th))
#define Sin(th) sin(3.14159265/180*(th))
#ifndef PI
#define PI 3.14159265
#endif

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    double x, y, z;
} Point;
typedef struct {
    double r, g, b;
} Color;

// Define the ColorName enum
typedef enum {
    RED, GREEN, BLUE, WHITE, BLACK, YELLOW, GREY, ORANGE, TAN, COLOR_COUNT
} ColorName;

// Declare an extern array to hold the predefined colors
extern const Color myColors[COLOR_COUNT];



void Print(const char* format , ...);
void Fatal(const char* format , ...);
unsigned int LoadTexBMP(const char* file);
void Project(double fov,double asp,double dim);
void ErrCheck(const char* where);
int  LoadOBJ(const char* file);
void axesHelper(double length);
void cube(double x,double y,double z,
                 double dx,double dy,double dz,
                 double th, float shiny);
void icosahedron(float x,float y,float z,float s,float th, float shiny);
void icosasphere(float x,float y,float z,float s, float shiny);
void ball(double x,double y,double z,double r, int emission, float shiny, int inc);
void lightOn(int ambient, int diffuse, int specular, int distance, float ylight, int emission, float shiny, int inc, int local, int zh);
void cylinder(double x,double y,double z,double br, double tr, double h, int sc,int emission, float shiny, Color color);
void truncatedPyramid(double x,double y,double z,double bl, double bw, double tl, double tw, double h,int emission, float shiny, Color color);
Point calculate_normal(Point p0, Point p1, Point p3);
void toriGate(double x, double y, double z, double s, double h, float shiny, unsigned int texture[]);
void lantern(double x, double y, double z, double s, double h, float shiny);
void bird(double x, double y, double z, double s, double h, float shiny);
void hemisphere(double x,double y,double z,double r,int emission, float shiny, Color color);
void PrintShaderLog(int obj,char* file);
char* ReadText(char *file);
void PrintProgramLog(int obj);
int CreateShader(GLenum type,char* file);
int CreateShaderProg(char* VertFile,char* FragFile);
void drawTessellatedPlane(int planeSizeX, int planeSizeZ, int gridSizeWidth, int gridSizeLength);

// Init
typedef void (*DisplayFunc)(void);
typedef void (*ReshapeFunc)(int width, int height);
typedef void (*KeyboardFunc)(unsigned char key, int x, int y);
typedef void (*SpecialFunc)(int key, int x, int y);
typedef void (*IdleFunc)(void);

void init(const char* windowName,
          DisplayFunc display,
          ReshapeFunc reshape,
          KeyboardFunc keyboard,
          SpecialFunc special,
          IdleFunc idle);

// Global variables that need to be accessed from other files 
extern int axes;
extern int mode;
extern int move;
extern int th;
extern int ph;
extern int fov;
extern int obj;
extern double asp;
extern double dim;
extern int light;
extern unsigned int texture[3];
extern int shader;


#ifdef __cplusplus
}
#endif

#endif
