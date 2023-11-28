#include "CSCIx229.h"

void init(const char* windowName,
          DisplayFunc display,
          ReshapeFunc reshape,
          KeyboardFunc keyboard,
          SpecialFunc special,
          IdleFunc idle) {
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
    glutInitWindowSize(800, 800);
    glutCreateWindow(windowName);

#ifdef USEGLEW
    if (glewInit() != GLEW_OK) Fatal("Error initializing GLEW\n");
#endif

    // Register the callback functions with GLUT here
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(special);
    glutIdleFunc(idle);

    // Load textures
    texture[0] = LoadTexBMP("textures/grass.bmp");
    texture[1] = LoadTexBMP("textures/tile.bmp");
    texture[2] = LoadTexBMP("textures/wood.bmp");

    // Create shader program
    shader = CreateShaderProg("shaders/terrainShaders/vert.glsl", "shaders/terrainShaders/frag.glsl");

    ErrCheck("init");
}
