#include "CSCIx229.h"


/**
 * Create a Tori gate 
 * at double x y z
 * with scale s, height h
*/
void toriGate(double x, double y, double z, double s, double h, float shiny, unsigned int texture[])
{
    glPushMatrix();
    glTranslated(x,y,z);
    glScaled(s,s,s);

    //WOOD TEXTURE

    glEnable(GL_TEXTURE_2D);
    glTexEnvi(GL_TEXTURE_ENV , GL_TEXTURE_ENV_MODE , GL_MODULATE);
    glBindTexture(GL_TEXTURE_2D, texture[2]);

    //Top Beam 1 Shimagi
    truncatedPyramid(0,  (h * 5/7) + (h * 5/25), 0,
                    h * 6/6, h * 2/17,
                    h * 7/6, h * 2/17, 
                    h * 1/12,
                    0, shiny, myColors[ORANGE]);
    //Top Beam 2 Shimagi
    truncatedPyramid(0,  (h * 5/7) + (h * 5/25) + (h * 1/12), 0,
                    h * 7/5, h * 1/17,
                    h * 7/5, h * 1/17,
                    h * 1/12,
                    0, shiny, myColors[ORANGE]);

    //Middle Beam Nuki
    truncatedPyramid(0,  h * 5/8 , 0,
                    h * 6/5, h * 1/15,
                    h * 6/5, h * 1/15, 
                    h * 1/10,
                    0, shiny, myColors[RED]);
    //Middle Connector Beam Gakuzuka
    truncatedPyramid(0,  (h * 5/8) + (h * 1/10), 0,
                    h * 1/10, h * 1/16,
                    h * 1/10, h * 1/16, 
                    h * 11/40,
                    0, shiny, myColors[RED]);

    glDisable(GL_TEXTURE_2D); // END WOOD TEXTURE


    //TILE TEXTURE
    glEnable(GL_TEXTURE_2D);
    glTexEnvi(GL_TEXTURE_ENV , GL_TEXTURE_ENV_MODE , GL_MODULATE);
    glBindTexture(GL_TEXTURE_2D, texture[0]);
        //Top Roof Kasagi 
    glPushMatrix();
    glRotated(20,1,0,0);
    truncatedPyramid(0,  (h * 5/7) + (h * 5/25) + (h * 1/17) + (h * 1/17), -h * 2/7,
                    h * 15/10, h * 3/15,
                    h * 15/10, h * 3/15,
                    h * 1/30,
                    0, shiny, myColors[GREEN]);
    glPopMatrix();
    glPushMatrix();
    glRotated(-20,1,0,0);
    truncatedPyramid(0,  (h * 5/7) + (h * 5/25) + (h * 1/17) + (h * 1/17), h * 2/7,
                    h * 15/10, h * 3/15,
                    h * 15/10, h * 3/15,
                    h * 1/30,
                    0, shiny, myColors[GREEN]);
    glPopMatrix();
        glPushMatrix();
    glRotated(20,1,0,0);
    truncatedPyramid(0,  (h * 5/7) + (h * 5/25) + (h * 1/20) + (h * 1/20), -h * 2/7,
                    h * 14/10, h * 3/15,
                    h * 14/10, h * 3/15,
                    h * 1/60,
                    0, shiny, myColors[RED]);
    glPopMatrix();
    glPushMatrix();
    glRotated(-20,1,0,0);
    truncatedPyramid(0,  (h * 5/7) + (h * 5/25) + (h * 1/20) + (h * 1/20), h * 2/7,
                    h * 14/10, h * 3/15,
                    h * 14/10, h * 3/15,
                    h * 1/60,
                    0, shiny, myColors[RED]);
    glPopMatrix();

    //Top Roof Beams
    truncatedPyramid(0,  (h * 5/7) + (h * 5/25) + (h * 1/12) + (h * 1/12) + (h * 1/30), 0,
                h * 7/5, h * 1/20,
                h * 7/5, h * 1/20,
                h * 1/30,
                0, shiny, myColors[GREEN]);
    truncatedPyramid(0,  (h * 5/7) + (h * 5/25) + (h * 1/12) + (h * 1/12) + (h * 1/30), 0,
                h * 7/5, h * 1/20,
                h * 7/5, h * 1/20,
                h * 1/30,
                0, shiny, myColors[GREEN]);

    glDisable(GL_TEXTURE_2D); //END TILE TEXTURE


    //GRASS TEXTURE
    glEnable(GL_TEXTURE_2D);
    glTexEnvi(GL_TEXTURE_ENV , GL_TEXTURE_ENV_MODE , GL_MODULATE);
    glBindTexture(GL_TEXTURE_2D, texture[0]);

    //Pillar Base Waraza
    cylinder(-h * 2/5,  0,  0,
              h * 1/12, h * 1/15, 
              h * 3/25, 5,
              0, shiny, myColors[GREY]);
    cylinder(h * 2/5,  0,  0,
              h * 1/12, h * 1/15, 
              h * 3/25, 5,
              0, shiny, myColors[GREY]);
    //Pillar top Base Daiwa
    cylinder(-h * 2/5,  (h * 5/7) + (h * 3/25),  0,
              h * 1/20, h * 1/15, 
              h * 2/25, 5,
              0, shiny, myColors[GREY]);
    cylinder (h * 2/5,  (h * 5/7) + (h * 3/25),  0,
              h * 1/20, h * 1/15, 
              h * 2/25, 5,
              0, shiny, myColors[GREY]);
    //Pillars Hashira
    cylinder(-h * 2/5,  h * 3/25,  0,
              h * 1/15, h * 1/20, 
              h * 5/7, 5,
              0, shiny, myColors[ORANGE]);
    cylinder(h * 2/5,  h * 3/25,  0,
              h * 1/15, h * 1/20, 
              h * 5/7, 5,
              0, shiny, myColors[ORANGE]);



    //Top Roof Kasagi 
    glPushMatrix();
    glRotated(20,1,0,0);
    truncatedPyramid(0,  (h * 5/7) + (h * 5/25) + (h * 1/17) + (h * 1/17), -h * 2/7,
                    h * 15/10, h * 3/15,
                    h * 15/10, h * 3/15,
                    h * 1/30,
                    0, shiny, myColors[GREEN]);
    glPopMatrix();
    glPushMatrix();
    glRotated(-20,1,0,0);
    truncatedPyramid(0,  (h * 5/7) + (h * 5/25) + (h * 1/17) + (h * 1/17), h * 2/7,
                    h * 15/10, h * 3/15,
                    h * 15/10, h * 3/15,
                    h * 1/30,
                    0, shiny, myColors[GREEN]);
    glPopMatrix();
        glPushMatrix();
    glRotated(20,1,0,0);
    truncatedPyramid(0,  (h * 5/7) + (h * 5/25) + (h * 1/20) + (h * 1/20), -h * 2/7,
                    h * 14/10, h * 3/15,
                    h * 14/10, h * 3/15,
                    h * 1/60,
                    0, shiny, myColors[RED]);
    glPopMatrix();
    glPushMatrix();
    glRotated(-20,1,0,0);
    truncatedPyramid(0,  (h * 5/7) + (h * 5/25) + (h * 1/20) + (h * 1/20), h * 2/7,
                    h * 14/10, h * 3/15,
                    h * 14/10, h * 3/15,
                    h * 1/60,
                    0, shiny, myColors[RED]);
    glPopMatrix();

    //Top Roof Beams
    truncatedPyramid(0,  (h * 5/7) + (h * 5/25) + (h * 1/12) + (h * 1/12) + (h * 1/30), 0,
                h * 7/5, h * 1/20,
                h * 7/5, h * 1/20,
                h * 1/30,
                0, shiny, myColors[GREEN]);
    truncatedPyramid(0,  (h * 5/7) + (h * 5/25) + (h * 1/12) + (h * 1/12) + (h * 1/30), 0,
                h * 7/5, h * 1/20,
                h * 7/5, h * 1/20,
                h * 1/30,
                0, shiny, myColors[GREEN]);


    //Connectors Kusabi Middle beam
    glPushMatrix();
    glRotated(90,0,0,1);
    truncatedPyramid((h * 5/8) + (h * 1/10),  (-h * 2/5) + (-h * 2/15), 0,
                h * 1/16, h * 1/20,
                h * 1/24, h * 1/25, 
                h * 1/8,
                0, shiny, myColors[GREY]);
    glPopMatrix();
    glPushMatrix();
    glRotated(-90,0,0,1);
    truncatedPyramid(-(h * 5/8) + -(h * 1/10),  (-h * 2/5) + (-h * 2/15), 0,
                h * 1/16, h * 1/20,
                h * 1/24, h * 1/25, 
                h * 1/8,
                0, shiny, myColors[GREY]);
    glPopMatrix();

    //Fence

    //HIKAEBASHIRA TOP
    truncatedPyramid(-h * 2/5,  (h * 3/9), 0,
                    h * 1/25, h * 6/5,
                    h * 1/25, h * 6/5,
                    h * 1/15,
                    0, shiny, myColors[RED]);
    truncatedPyramid(h * 2/5,  (h * 3/9), 0,
                    h * 1/25, h * 6/5,
                    h * 1/25, h * 6/5,
                    h * 1/15,
                    0, shiny, myColors[RED]);

    //HIKAEBASHIRA Bottom
    truncatedPyramid(-h * 2/5,  (h * 2/10), 0,
                    h * 1/25, h * 6/5,
                    h * 1/25, h * 6/5,
                    h * 1/15,
                    0, shiny, myColors[RED]);
    truncatedPyramid(h * 2/5,  (h * 2/10), 0,
                    h * 1/25, h * 6/5,
                    h * 1/25, h * 6/5,
                    h * 1/15,
                    0, shiny, myColors[RED]);

    //FRONT FENCE
    glPushMatrix();
    glTranslatef(0, 0, h * 2/4);
    //Fence pillars Hashira
    cylinder(-h * 2/5,  h * 1/25,  0,
              h * 1/20, h * 1/30, 
              h * 3/8, 5,
              0, shiny, myColors[ORANGE]);
    cylinder(h * 2/5,  h * 1/25,  0,
              h * 1/20, h * 1/30, 
              h * 3/8, 5,
              0, shiny, myColors[ORANGE]);
    //Fence Pillar Base Waraza
    truncatedPyramid(-h * 2/5,  0,  0,
              h * 1/10, h * 1/10, 
              h * 1/10, h * 1/10, 
              h * 1/25,
              0, shiny, myColors[GREY]);
    truncatedPyramid(h * 2/5,  0,  0,
              h * 1/10, h * 1/10, 
              h * 1/10, h * 1/10, 
              h * 1/25,
              0, shiny, myColors[GREY]);
    //Fence Pillar top Base Daiwa
    truncatedPyramid(-h * 2/5,  (h * 3/8) + (h * 1/25),  0,
              h * 1/10, h * 1/10, 
              h * 1/15, h * 1/10, 
              h * 1/30,
              0, shiny, myColors[GREY]);
    truncatedPyramid (h * 2/5,  (h * 3/8) + (h * 1/25),  0,
              h * 1/10, h * 1/10, 
              h * 1/15, h * 1/10, 
              h * 1/30,
              0, shiny, myColors[GREY]);
    glPopMatrix();


    glPushMatrix();
    //BACK FENCE
    glTranslatef(0, 0, -h * 2/4);
    //Fence pillars Hashira
    cylinder(-h * 2/5,  h * 1/25,  0,
              h * 1/20, h * 1/30, 
              h * 3/8, 5,
              0, shiny, myColors[ORANGE]);
    cylinder(h * 2/5,  h * 1/25,  0,
              h * 1/20, h * 1/30, 
              h * 3/8, 5,
              0, shiny, myColors[ORANGE]);
    //Fence Pillar Base Waraza
    truncatedPyramid(-h * 2/5,  0,  0,
              h * 1/10, h * 1/10, 
              h * 1/10, h * 1/10, 
              h * 1/25,
              0, shiny, myColors[GREY]);
    truncatedPyramid(h * 2/5,  0,  0,
              h * 1/10, h * 1/10, 
              h * 1/10, h * 1/10, 
              h * 1/25,
              0, shiny, myColors[GREY]);
    //Fence Pillar top Base Daiwa
    truncatedPyramid(-h * 2/5,  (h * 3/8) + (h * 1/25),  0,
              h * 1/10, h * 1/10, 
              h * 1/15, h * 1/10, 
              h * 1/30,
              0, shiny, myColors[GREY]);
    truncatedPyramid (h * 2/5,  (h * 3/8) + (h * 1/25),  0,
              h * 1/10, h * 1/10, 
              h * 1/15, h * 1/10, 
              h * 1/30,
              0, shiny, myColors[GREY]);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();
}

void lantern(double x, double y, double z, double s, double h, float shiny)
{
    glPushMatrix();
    glTranslated(x,y,z);
    glScaled(s,s,s);
    //lantern
    cylinder(0,0,0,
             h * 1/3, h * 1/3,
             h * 2/4, 6, 
             1, shiny, myColors[TAN]);

    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glPushMatrix();
    glScaled(1.1,1.0,1.1);
    cylinder(0,0,0,
             h * 1/3, h * 1/3,
             h * 2/4, 6, 
             0, shiny, myColors[RED]);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); 
    glPopMatrix();

    hemisphere(0,0,0,
               h * 1/3, 0, shiny, myColors[TAN]);
    glPushMatrix();
    glRotated(180,1,0,0);
    hemisphere(0,- h* 2/4,0,
               h * 1/3, 0, shiny, myColors[TAN]);
    glPopMatrix();

    truncatedPyramid(0, (h * 2/4) + (h * 1/3) - (h * 1/10),0,
             h * 1/4, h * 1/4,
             h * 1/6, h * 1/6,
             h * 2/10,
             0, 0, myColors[BLACK]);

    glPopMatrix();
}

void bird(double x, double y, double z, double s, double h, float shiny)
{
    glPushMatrix();
    glTranslated(x,y,z);
    glScaled(s,s,s);

    glPopMatrix();
}