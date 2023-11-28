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
#include "Globals.h"
#include "ImGuiHelper.h"

#include "imgui.h"
#include "imgui_impl_glut.h"
#include "imgui_impl_opengl2.h"


int ntex=0;    //  Texture
double t = 0;


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
      id = glGetUniformLocation(shader,"uTileSize");
      glUniform1f(id,uTileSize);
      id = glGetUniformLocation(shader,"uResolution");
      glUniform1f(id,planeSize);

      id = glGetUniformLocation(shader,"uTime");
      
      glUniform1f(id,t);

      drawTessellatedPlane(planeSize, planeSize,256,256);
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

   RenderImGuiGeneralControls();

   ImGui::Render();
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
