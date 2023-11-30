#include "Globals.h"

int axes=1;       //  Display axes
int mode=1;       //  Projection mode
int move=1;       //  Move light
int th=0;         //  Azimuth of view angle
int ph=0;         //  Elevation of view angle
int fov=75;       //  Field of view (for perspective)
int obj=0;        //  Scene/opbject selection
double asp=1;     //  Aspect ratio
double dim=6;     //  Size of world
int light     =   1;  // Lighting
int one       =   1;  // Unit value
int distance  =   5;  // Light distance
int inc       =  10;  // Ball increment
int smooth    =   1;  // Smooth/Flat shading
int local     =   0;  // Local Viewer Model
int emission  =   0;  // Emission intensity (%)
int ambient   =   20;  // Ambient intensity (%)
int diffuse   =  80;  // Diffuse intensity (%)
int specular  =   0;  // Specular intensity (%)
int shininess =   0;  // Shininess (power of two)
float shiny   =   1;  // Shininess (value)
int zh        =  90;  // Light azimuth
float ylight  =   1;  // Elevation of light
//Shader
int shader = 0;
unsigned int texture[3];
float uScale=8.5;
float uPersistence=2.0;
float uLacunarity=4.0;
float uExponentiation=2;
float uHeight=2.5;
int uOctaves=4.0;
int uTileSize = 5.0f;
int planeSize = 10.0f;


int texWidth = 256; // Width of the texture
int texHeight = 256; // Height of the texture

//state
ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
