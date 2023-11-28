// Globals.h

#ifndef GLOBALS_H
#define GLOBALS_H
#include"imgui.h"

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
extern int one;
extern int distance;
extern int inc;
extern int smooth;
extern int local;
extern int emission;
extern int ambient;
extern int diffuse;
extern int specular;
extern int shininess;
extern float shiny;
extern int zh;
extern float ylight;
extern int shader;
extern unsigned int texture[3];
extern float uScale;
extern float uPersistence;
extern float uLacunarity;
extern float uExponentiation;
extern float uHeight;
extern int uOctaves;
extern ImVec4 clear_color;

#endif
