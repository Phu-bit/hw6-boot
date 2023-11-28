/*
 *  Lighting
 *
 *  Demonstrates basic lighting using a cube, sphere and icosahedron.
 *
 *  Key bindings:
 *  l          Toggles lighting
 *  a/A        Decrease/increase ambient light
 *  d/D        Decrease/increase diffuse light
 *  s/S        Decrease/increase specular light
 *  e/E        Decrease/increase emitted light
 *  n/N        Decrease/increase shininess
 *  F1         Toggle smooth/flat shading
 *  F2         Toggle local viewer mode
 *  F3         Toggle light distance (1/5)
 *  F8         Change ball increment
 *  F9         Invert bottom normal
 *  m          Toggles light movement
 *  []         Lower/rise light
 *  p          Toggles ortogonal/perspective projection
 *  o          Cycles through objects
 *  +/-        Change field of view of perspective
 *  x          Toggle axes
 *  arrows     Change view angle
 *  PgDn/PgUp  Zoom in and out
 *  0          Reset view angle
 *  ESC        Exit
 */
#include "CSCIx229.h"

#include "imgui.h"
#include "imgui_impl_glut.h"
#include "imgui_impl_opengl2.h"


int axes=1;       //  Display axes
int mode=1;       //  Projection mode
int move=1;       //  Move light
int th=0;         //  Azimuth of view angle
int ph=0;         //  Elevation of view angle
int fov=75;       //  Field of view (for perspective)
int obj=0;        //  Scene/opbject selection
double asp=1;     //  Aspect ratio
double dim=6;     //  Size of world
int ntex=0;    //  Texture
double t = 0;
// Light values
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
float ylight  =   0;  // Elevation of light

//Shader
int shader = 0;
unsigned int texture[3];

//perlin noise
float uScale=8.5;
float uPersistence=2.0;
float uLacunarity=4.0;
float uExponentiation=2;
float uHeight=2.5;
int uOctaves=4.0;

//state
static ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);



/*
 *  OpenGL (GLUT) calls this routine to display the scene
 */
void display()
{

   glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
   //  Enable Z-buffering in OpenGL
   glEnable(GL_DEPTH_TEST);
   //  Undo previous transformations
   glLoadIdentity();
   //  Perspective - set eye position
   if (mode)
   {
      double Ex = -2*dim*Sin(th)*Cos(ph);
      double Ey = +2*dim        *Sin(ph);
      double Ez = +2*dim*Cos(th)*Cos(ph);
      gluLookAt(Ex,Ey,Ez , 0,0,0 , 0,Cos(ph),0);
   }
   //  Orthogonal - set world orientation
   else
   {
      glRotatef(ph,1,0,0);
      glRotatef(th,0,1,0);
   }

   //  Light switch
   if (light)
   {
      
      lightOn(ambient, diffuse, specular, distance, ylight, emission, shiny, inc, local, zh);

   }
   else
      glDisable(GL_LIGHTING);

   //  Draw individual objects
   if (obj==1)
   {  
   //Other scene, if nessesary
      
   } 
   else if (obj==2)
   {     
      //other scene, if nessesary. 
   }      
   //  Basic scene
   else
   {
      //Scene

      // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
      glUseProgram(shader);
      int id = glGetUniformLocation(shader,"uScale");
      glUniform1f(id,uScale);
      id = glGetUniformLocation(shader,"uPersistence");
      glUniform1f(id,uPersistence);
      id = glGetUniformLocation(shader,"uLacunarity");
      glUniform1f(id,uLacunarity);
      id = glGetUniformLocation(shader,"uExponentiation");
      glUniform1f(id,uExponentiation);
      id = glGetUniformLocation(shader,"uHeight");
      glUniform1f(id,uHeight);
      id = glGetUniformLocation(shader,"uOctaves");
      glUniform1i(id,uOctaves);

      id = glGetUniformLocation(shader,"uTime");
      
      glUniform1f(id,t);

      drawTessellatedPlane(10,10,256,256);
      glUseProgram(0);

   }

   //  Draw axes - no lighting from here on
   glDisable(GL_LIGHTING);
   if (axes)
   {
      axesHelper(2.0);
   }

   //  Display parameters
   glColor3f(1.0,1.0,1.0);
   glWindowPos2i(5,5);
   Print("Dim=%.1f FOV=%d", dim, fov);
   glWindowPos2i(5,25);
   Print("Scale=%.1f Persistence=%.1f Lacunarity=%.1f", uScale, uPersistence, uLacunarity);
   glWindowPos2i(5,45);
   Print("Exponentiation=%.1f Height=%.1f Octaves=%d", uExponentiation, uHeight, uOctaves);
   glWindowPos2i(5,65);

   Print("Press 'o' to change models");

   // imGui
   ImGui_ImplOpenGL2_NewFrame();
   ImGui_ImplGLUT_NewFrame();
   ImGui::NewFrame();
   ImGuiIO& io = ImGui::GetIO();

   ImGui::Begin("hello world");
   ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color
   ImGui::Text("App average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
   ImGui::End();

   ImGui::Render();
   // glViewport(0, 0, (GLsizei)io.DisplaySize.x, (GLsizei)io.DisplaySize.y);
   glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w);

   ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());

   //  Render the scene and make it visible
   ErrCheck("display");
   glFlush();
   glutSwapBuffers();
}

/*
 *  GLUT calls this routine when the window is resized
 */
void idle()
{
   //  Elapsed time in seconds
   t = glutGet(GLUT_ELAPSED_TIME)/1000.0;
   zh = fmod(90*t,360.0);
   //  Tell GLUT it is necessary to redisplay the scene
   glutPostRedisplay();
}

/*
 *  GLUT calls this routine when an arrow key is pressed
 */
void special(int key,int x,int y)
{
   //  Right arrow key - increase angle by 5 degrees
   if (key == GLUT_KEY_RIGHT)
      th += 10;
   //  Left arrow key - decrease angle by 5 degrees
   else if (key == GLUT_KEY_LEFT)
      th -= 10;
   //  Up arrow key - increase elevation by 5 degrees
   else if (key == GLUT_KEY_UP)
      ph += 10;
   //  Down arrow key - decrease elevation by 5 degrees
   else if (key == GLUT_KEY_DOWN)
      ph -= 10;
   //  PageUp key - increase dim
   else if (key == GLUT_KEY_PAGE_DOWN)
      dim += 0.1;
   //  PageDown key - decrease dim
   else if (key == GLUT_KEY_PAGE_UP && dim>1)
      dim -= 0.1;
   //  Smooth color model
   else if (key == GLUT_KEY_F1)
      smooth = 1-smooth;
   //  Local Viewer
   else if (key == GLUT_KEY_F2)
      local = 1-local;
   else if (key == GLUT_KEY_F3)
      distance = (distance==1) ? 5 : 1;
   //  Toggle ball increment
   else if (key == GLUT_KEY_F8)
      inc = (inc==10)?3:10;
   //  Flip sign
   else if (key == GLUT_KEY_F9)
      one = -one;
   //  Keep angles to +/-360 degrees
   th %= 360;
   ph %= 360;
   //  Update projection
   Project(mode?fov:0,asp,dim);
   //  Tell GLUT it is necessary to redisplay the scene
   glutPostRedisplay();
}

/*
 *  GLUT calls this routine when a key is pressed
 */
void key(unsigned char ch,int x,int y)
{
   //  Exit on ESC
   if (ch == 27)
      exit(0);
   //  Reset view angle
   else if (ch == '0')
      th = ph = 0;
   //  Toggle axes
   else if (ch == 'x' || ch == 'X')
      axes = 1-axes;
   //  Toggle lighting
   else if (ch == 'l' || ch == 'L')
      light = 1-light;
   //  Switch projection mode
   else if (ch == 'p' || ch == 'P')
      mode = 1-mode;
   //  Toggle light movement
   else if (ch == 'm' || ch == 'M')
      move = 1-move;
   //  Move light
   else if (ch == '<')
      zh += 1;
   else if (ch == '>')
      zh -= 1;
   //  Change field of view angle
   else if (ch == '-' && ch>1)
      fov--;
   else if (ch == '=' && ch<179)
      fov++;
   //  Switch scene/object
   else if (ch == 'o')
      obj = (obj+1)%3;
   else if (ch == 'O')
      obj = (obj+2)%3;
      else if (ch == 'z')
      uScale = uScale > 1 ? uScale - 0.1 : 1;  // prevent it from being less than 1
   else if (ch == 'Z')
      uScale += 0.1;
   // Persistence
   else if (ch == 'c')
      uPersistence = uPersistence > 0.1 ? uPersistence - 0.1 : 0.1;  // prevent it from being too low
   else if (ch == 'C')
      uPersistence += 0.1;
   // Lacunarity
   else if (ch == 'v')
      uLacunarity = uLacunarity > 1.1 ? uLacunarity - 0.1 : 1.1;  // keep it above 1
   else if (ch == 'V')
      uLacunarity += 0.1;
   // Exponentiation
   else if (ch == 'b')
      uExponentiation = uExponentiation > 1 ? uExponentiation - 0.1 : 1;  // keep it sane
   else if (ch == 'B')
      uExponentiation += 0.1;
   // Height
   else if (ch == 'n')
      uHeight = uHeight > 1 ? uHeight - 0.1 : 1;  // prevent it from being less than 1
   else if (ch == 'N')
      uHeight += 0.1;
   // Octaves
   else if (ch == ',')
      uOctaves = uOctaves > 1 ? uOctaves - 1 : 1;  // prevent it from being less than 1
   else if (ch == '.')
      uOctaves += 1;

   //  Translate shininess power to value (-1 => 0)
   shiny = shininess<0 ? 0 : pow(2.0,shininess);
   //  Reproject
   Project(mode?fov:0,asp,dim);
   //  Animate if requested
   glutIdleFunc(move?idle:NULL);
   //  Tell GLUT it is necessary to redisplay the scene
   glutPostRedisplay();
}

/*
 *  GLUT calls this routine when the window is resized
 */
void reshape(int width,int height)
{
   ImGuiIO& io = ImGui::GetIO();

   //  Ratio of the width to the height of the window
   asp = (height>0) ? (double)width/height : 1;
   //  Set the viewport to the entire window
   glViewport(0,0, RES*width,RES*height);
   io.DisplaySize = ImVec2((float)width, (float)height);

   //  Set projection
   Project(mode?fov:0,asp,dim);
}

/*
 *  Start up GLUT and tell it what to do
 */
#include "CSCIx229.h"

int main(int argc, char* argv[]) {
    glutInit(&argc, argv);

    init("3D Scene", display, reshape, key, special, idle);
    // imgui
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;         // Enable Docking
    io.DisplaySize = ImVec2((float)800, (float)800);
    ImGui::StyleColorsDark();
    ImGui_ImplGLUT_Init();
    ImGui_ImplOpenGL2_Init();
    ImGui_ImplGLUT_InstallFuncs();

    glutMainLoop();

    // Cleanup
    ImGui_ImplOpenGL2_Shutdown();
    ImGui_ImplGLUT_Shutdown();
    ImGui::DestroyContext();

    return 0;
}
