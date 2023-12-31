#include "CSCIx229.h"

 /**
 * Tessalated Plane
 * Function to draw a tessellated plane of size gridSizeWidthxgridSizeWidth
 * planesize X, planesize Z, gridsize W, gridsize L
 */
void drawTessellatedPlane(int planeSizeX, int planeSizeZ, int gridSizeWidth, int gridSizeLength)
{
    int i, j;
    float stepX = (float)planeSizeX / (float)gridSizeWidth; // Step size in x direction
    float stepZ = (float)planeSizeZ / (float)gridSizeLength; // Step size in z direction
    float startX = -planeSizeX / 2.0f; // Starting x value
    float startZ = -planeSizeZ / 2.0f; // Starting z value
    float x, z;
    
    glBegin(GL_TRIANGLES);
    for (i = 0; i < gridSizeWidth; i++)
    {
        x = startX + i * stepX; // Current x position
        for (j = 0; j < gridSizeLength; j++)
        {
            z = startZ + j * stepZ; // Current z position
            
            // Define the vertices for two triangles (a quad) to cover the 'grid cell'
            glVertex3f(x, 0.0f, z);
            glVertex3f(x + stepX, 0.0f, z);
            glVertex3f(x, 0.0f, z + stepZ);

            glVertex3f(x, 0.0f, z + stepZ);
            glVertex3f(x + stepX, 0.0f, z);
            glVertex3f(x + stepX, 0.0f, z + stepZ);
        }
    }
    glEnd();
}

void drawGrid(int planeSize, int gridSizeWidth, int gridSizeLength)
{
    int id = glGetUniformLocation(shader,"uOffset");
    glUniform2f(id, 0.0f, 0.0f); // No offset for the first plane

    drawTessellatedPlane(planeSize, planeSize,gridSizeWidth, gridSizeLength);

    id = glGetUniformLocation(shader,"uOffset");
    glUniform2f(id, planeSize, 0.0f);
    drawTessellatedPlane(planeSize, planeSize,gridSizeWidth,gridSizeLength);

    id = glGetUniformLocation(shader,"uOffset");
    glUniform2f(id, -planeSize, 0.0f);
    drawTessellatedPlane(planeSize, planeSize,gridSizeWidth,gridSizeLength);

    id = glGetUniformLocation(shader,"uOffset");
    glUniform2f(id, planeSize, -planeSize);
    drawTessellatedPlane(planeSize, planeSize,gridSizeWidth,gridSizeLength);

    id = glGetUniformLocation(shader,"uOffset");
    glUniform2f(id, 0.0f, -planeSize);
    drawTessellatedPlane(planeSize, planeSize,gridSizeWidth,gridSizeLength);

    id = glGetUniformLocation(shader,"uOffset");
    glUniform2f(id, 0.0f, planeSize);
    drawTessellatedPlane(planeSize, planeSize,gridSizeWidth,gridSizeLength);

    id = glGetUniformLocation(shader,"uOffset");
    glUniform2f(id, planeSize, planeSize);
    drawTessellatedPlane(planeSize, planeSize,gridSizeWidth,gridSizeLength);

    id = glGetUniformLocation(shader,"uOffset");
    glUniform2f(id, -planeSize, planeSize);
    drawTessellatedPlane(planeSize, planeSize,gridSizeWidth,gridSizeLength);

    id = glGetUniformLocation(shader,"uOffset");
    glUniform2f(id, -planeSize, -planeSize);
    drawTessellatedPlane(planeSize, planeSize,gridSizeWidth,gridSizeLength);


}