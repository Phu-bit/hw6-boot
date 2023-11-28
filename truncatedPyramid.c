#include "CSCIx229.h"

/**
 * Truncated Pyramid
 * at double x y z,
 * base length bl base width bw
 * top length tl top width tw
 * height h
 * int emission, float shiny, float color[]
 * 
*/
void truncatedPyramid(double x,double y,double z,
              double bl, double bw, double tl, double tw, double h,
              int emission, float shiny, Color color)
{

    int i;
    // Material properties (if needed)
    float black[]  = {0.0,0.0,0.0,1.0};
    glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,black);

    if(shiny > 0)
    {
        float white[]   = {1.0,1.0,1.0,1.0};

        //float mat_specular[] = {1.0, 1.0, 1.0, 1.0};
        glMaterialfv(GL_FRONT,GL_SPECULAR,white);
        glMaterialf(GL_FRONT,GL_SHININESS,shiny);
    }

    glPushMatrix();
    glTranslated(x, y, z);

    glColor3d(color.r, color.g, color.b);

    // Vertices for bottom and top faces
    double vertices[] = {
        -bl/2, 0, -bw/2,   // 0
         bl/2, 0, -bw/2,   // 1
         bl/2, 0,  bw/2,   // 2
        -bl/2, 0,  bw/2,   // 3
        -tl/2, h, -tw/2,   // 4
         tl/2, h, -tw/2,   // 5
         tl/2, h,  tw/2,   // 6
        -tl/2, h,  tw/2    // 7
    };

    // Indices to draw the bottom and top faces using GL_QUADS
    GLfloat texCoords[] = {
        0.0f, 0.0f,
        1.0f, 0.0f,
        1.0f, 1.0f,
        0.0f, 1.0f,
    };
    // Indices for sides
    GLfloat texCoordsSide[] = {
        // Front face
        0.0f, 0.0f,  // Vertex 3
        1.0f, 0.0f,  // Vertex 2
        1.0f, 1.0f,  // Vertex 6
        0.0f, 1.0f,  // Vertex 6

        // Back face
        0.0f, 0.0f,  // Vertex 4
        1.0f, 0.0f,  // Vertex 5
        1.0f, 1.0f,  // Vertex 6
        0.0f, 1.0f,  // Vertex 7

        // Right face
        0.0f, 0.0f,  // Vertex 16
        1.0f, 0.0f,  // Vertex 17
        1.0f, 1.0f,  // Vertex 18
        0.0f, 1.0f,  // Vertex 19

        // Left face
        0.0f, 0.0f,  // Vertex 20
        1.0f, 0.0f,  // Vertex 21
        1.0f, 1.0f,  // Vertex 22
        0.0f, 1.0f,  // Vertex 23
    };


    // Indices to draw the textures for bottom and top faces
    unsigned int faceIndices[] = {
        0, 1, 2, 3,  // Bottom face
        7, 6, 5, 4   // Top face
    };

    // Indices to draw the sides using GL_QUAD_STRIP
    // unsigned int sideIndices[] = {
    //     0, 4, 1, 5, 2, 6, 3, 7, 0, 4  // Around the sides
    // };

    unsigned int sideIndices[] = {
        3, 2, 6, 7,
        0, 3, 7, 4,
        1, 0, 4, 5,
        2, 1, 5, 6
    };



    // Draw bottom and top faces using indices
    glBegin(GL_QUADS);
    // Normal for the bottom face
    glNormal3d(0, -1, 0);
    for (i = 0; i < 4; i++) 
    {
        int idx = faceIndices[i] * 3;
        int idxT = i * 2;
        glTexCoord2f(texCoords[idxT],texCoords[idxT + 1]);
        glVertex3d(vertices[idx], vertices[idx + 1], vertices[idx + 2]);
    }
    // Normal for the top face
    glNormal3d(0, 1, 0);
    for (i = 4; i < 8; i++) 
    {
        int idx = faceIndices[i] * 3;
        int idxT = (i - 4) * 2;
        glTexCoord2f(texCoords[idxT ],texCoords[idxT + 1]);
        glVertex3d(vertices[idx], vertices[idx + 1], vertices[idx + 2]);
    }

    // SIDES

        // glTexCoord2f(0.0, 1.0);glVertex3d( -bl/2, 0,  bw/2);
        // glTexCoord2f(1.0, 1.0);glVertex3d(bl/2, 0,  bw/2);
        // glTexCoord2f(1.0, 0.0);glVertex3d(tl/2, h,  tw/2);
        // glTexCoord2f(0.0, 0.0);glVertex3d(-tl/2, h,  tw/2);


    for (int i = 0; i < 16; i+=4) 
    {
        // Calculate the normal for the current face
        Point p0 = {vertices[sideIndices[i] * 3], vertices[sideIndices[i] * 3 + 1], vertices[sideIndices[i] * 3 + 2]};
        Point p1 = {vertices[sideIndices[i + 1] * 3], vertices[sideIndices[i + 1] * 3 + 1], vertices[sideIndices[i + 1] * 3 + 2]};
        Point p2 = {vertices[sideIndices[i + 2] * 3], vertices[sideIndices[i + 2] * 3 + 1], vertices[sideIndices[i + 2] * 3 + 2]};
        Point normal = calculate_normal(p0, p1, p2);
        glNormal3d(normal.x, normal.y, normal.z);

        // Draw the current face using its vertices
        for (int j = 0; j < 4; j++) 
        {
            int idx = sideIndices[i + j] * 3;
            int idxT = (i + j) * 2;
            glTexCoord2f(texCoordsSide[idxT], texCoordsSide[idxT + 1]);
            glVertex3d(vertices[idx], vertices[idx + 1], vertices[idx + 2]);
        }
    }
glEnd();
// Draw the side surfaces using indices
// glBegin(GL_QUAD_STRIP);
// for (int i = 0; i < 3; i += 2) {
//     // Extract points
//     Point p0 = {vertices[3*sideIndices[i]], vertices[3*sideIndices[i]+1], vertices[3*sideIndices[i]+2]};
//     Point p1 = {vertices[3*sideIndices[i+1]], vertices[3*sideIndices[i+1]+1], vertices[3*sideIndices[i+1]+2]};
//     Point p2 = {vertices[3*sideIndices[i+2]], vertices[3*sideIndices[i+2]+1], vertices[3*sideIndices[i+2]+2]};

//     // Calculate normal
    

//     // Apply normal
//     if (i >= 8)
//     {
//         Point p0 = {vertices[3*sideIndices[i]], vertices[3*sideIndices[i]+1], vertices[3*sideIndices[i]+2]};
//         Point p1 = {vertices[3*sideIndices[i+1]], vertices[3*sideIndices[i+1]+1], vertices[3*sideIndices[i+1]+2]};
//         Point p2 = {vertices[3*sideIndices[5+1]], vertices[3*sideIndices[5+1]+1], vertices[3*sideIndices[5+2]+2]};

//         Point normal = calculate_normal(p0, p2, p1);
//         glNormal3d(normal.x, normal.y,normal.z);

//     }else
//     {    
//         Point normal = calculate_normal(p0, p1, p2);

//     glNormal3d(normal.x, normal.y, normal.z);

//     }
//     int idxT = i * 4;

//     // Use vertices
//     glTexCoord2d(texCoordsSide[idxT], texCoordsSide[idxT+1]);
//     glVertex3d(p0.x, p0.y, p0.z);

//     glTexCoord2d(texCoordsSide[idxT+2], texCoordsSide[idxT+3]);
//     glVertex3d(p1.x, p1.y, p1.z);

// }
// glEnd();



glPopMatrix();
}