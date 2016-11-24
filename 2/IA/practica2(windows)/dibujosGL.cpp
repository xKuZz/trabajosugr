 

#include "include/GL/glui.h"
#include <cstdlib>
#include <iostream>
#include "dibujosGL.h"
#include "retrato.hpp"
 

 using namespace std;

void drawCube(double x, double y, double z, double base, double alto)
{

    glShadeModel(GL_FLAT);
    //ponerMaterial(1.0f, 0.0f, 0.0f);
    glBegin(GL_QUADS);       //cara frontal
    glVertex3f( x-(base/2),  y,  z+(base/2));
    glVertex3f( x+(base/2),  y,  z+(base/2));
    glVertex3f( x+(base/2),  y+alto,  z+(base/2));
    glVertex3f( x-(base/2),  y+alto,  z+(base/2));
    glEnd();

    //ponerMaterial(1.0f, 1.0f, 1.0f);


    glBegin(GL_QUADS);       //cara trasera
    glVertex3f( x-(base/2),  y,  z-(base/2));
    glVertex3f( x+(base/2),  y,  z-(base/2));
    glVertex3f( x+(base/2),  y+alto,  z-(base/2));
    glVertex3f( x-(base/2),  y+alto,  z-(base/2));
    glEnd();

    //ponerMaterial(0.0f, 0.0f, 1.0f);
    glBegin(GL_QUADS);       //cara lateral izq
    glVertex3f( x-(base/2) ,y, z+(base/2));
    glVertex3f( x-(base/2) ,y, z-(base/2));
    glVertex3f( x-(base/2) ,y+alto, z-(base/2));
    glVertex3f( x-(base/2) ,y+alto, z+(base/2));
    glEnd();

    //ponerMaterial(1.0f, 1.0f, 0.0f);
    glBegin(GL_QUADS);       //cara lateral dcha
    glVertex3f( x+(base/2) ,y, z+(base/2));
    glVertex3f( x+(base/2) ,y, z-(base/2));
    glVertex3f( x+(base/2) ,y+alto, z-(base/2));
    glVertex3f( x+(base/2) ,y+alto, z+(base/2));
    glEnd(); 

    //ponerMaterial(0.0f, 1.0f, 1.0f);
    glBegin(GL_QUADS);       //cara arriba
    glVertex3f( x-(base/2), y+alto,  z+(base/2));
    glVertex3f( x-(base/2), y+alto,  z-(base/2));
    glVertex3f( x+(base/2), y+alto,  z-(base/2));
    glVertex3f( x+(base/2), y+alto,  z+(base/2));
    glEnd();
 
    //ponerMaterial(1.0f, 0.0f, 1.0f);
    glBegin(GL_QUADS);       //cara abajo
    glVertex3f( x-(base/2), y,  z+(base/2));
    glVertex3f( x-(base/2), y,  z-(base/2));
    glVertex3f( x+(base/2), y,  z-(base/2));
    glVertex3f( x+(base/2), y,  z+(base/2));
    glEnd();



    ponerMaterial(0,0,0);

    glBegin(GL_LINE_LOOP);       //cara frontal
    glVertex3f( x-(base/2),  y,  z+(base/2));
    glVertex3f( x+(base/2),  y,  z+(base/2));
    glVertex3f( x+(base/2),  y+alto,  z+(base/2));
    glVertex3f( x-(base/2),  y+alto,  z+(base/2));
    glEnd();

    //ponerMaterial(1.0f, 1.0f, 1.0f);


    // glBegin(GL_LINE_LOOP);       //cara trasera
    // glVertex3f( x-(base/2),  y,  z-(base/2));
    // glVertex3f( x+(base/2),  y,  z-(base/2));
    // glVertex3f( x+(base/2),  y+alto,  z-(base/2));
    // glVertex3f( x-(base/2),  y+alto,  z-(base/2));
    // glEnd();

    // //ponerMaterial(0.0f, 0.0f, 1.0f);
    glBegin(GL_LINE_LOOP);       //cara lateral izq
    glVertex3f( x-(base/2) ,y, z+(base/2));
    glVertex3f( x-(base/2) ,y, z-(base/2));
    glVertex3f( x-(base/2) ,y+alto, z-(base/2));
    glVertex3f( x-(base/2) ,y+alto, z+(base/2));
    glEnd();

    // //ponerMaterial(1.0f, 1.0f, 0.0f);
    glBegin(GL_LINE_LOOP);       //cara lateral dcha
    glVertex3f( x+(base/2) ,y, z+(base/2));
    glVertex3f( x+(base/2) ,y, z-(base/2));
    glVertex3f( x+(base/2) ,y+alto, z-(base/2));
    glVertex3f( x+(base/2) ,y+alto, z+(base/2));
    glEnd(); 

    // //ponerMaterial(0.0f, 1.0f, 1.0f);
    // glBegin(GL_LINE_LOOP);       //cara arriba
    // glVertex3f( x-(base/2), y+alto,  z+(base/2));
    // glVertex3f( x-(base/2), y+alto,  z-(base/2));
    // glVertex3f( x+(base/2), y+alto,  z-(base/2));
    // glVertex3f( x+(base/2), y+alto,  z+(base/2));
    // glEnd();
 
    // //ponerMaterial(1.0f, 0.0f, 1.0f);
    // glBegin(GL_LINE_LOOP);       //cara abajo
    // glVertex3f( x-(base/2), y,  z+(base/2));
    // glVertex3f( x-(base/2), y,  z-(base/2));
    // glVertex3f( x+(base/2), y,  z-(base/2));
    // glVertex3f( x+(base/2), y,  z+(base/2));
    // glEnd();


}

void ponerMaterial(float R, float G, float B){
  glShadeModel(GL_SMOOTH);
  GLfloat ambient1[4]={R,G,B,1};
  GLfloat diffuse1[4]={R,G,B,1};
  GLfloat specular1[4]={R,G,B,1};
  glMaterialfv(GL_FRONT,GL_AMBIENT,(GLfloat *) &ambient1);
  glMaterialfv(GL_FRONT,GL_DIFFUSE,(GLfloat *) &diffuse1);
  glMaterialfv(GL_FRONT,GL_SPECULAR,(GLfloat *) &specular1);
  glMaterialf(GL_FRONT,GL_SHININESS,10);
}


void drawTree(double x, double y, double z, double base, double alto)
{
  

  
  ponerMaterial(0,1,0);
  drawCube(x,y,z,base,0.1);

  ponerMaterial(0.4,0.15,0.15);
  drawCube(x,y,z,base/10,alto/2);



  ponerMaterial(0,1,0);

  drawCube(x,y+alto/2,z,base,alto/2);


}



void drawWall(double x, double y, double z, double base, double alto)
{
  ponerMaterial(0.45,0.25,0.13);
  drawCube(x,y,z,1,0.1);
  for (int i=0; i<10; i++){
      ponerMaterial(0.45,0.25,0.13);
      drawCube(x,y+0.1*i,z,1,0.1);
  }
}

void drawQuesitoDeFrente(double x, double y, double z){
      ponerMaterial(0,0,0);
      glBegin(GL_TRIANGLES);
      glVertex3f(x,    y+0.1, z+0.3);
      glVertex3f(x+0.3,y+0.1, z-0.3);
      glVertex3f(x-0.3,y+0.1, z-0.3);
      glEnd();

      ponerMaterial(1,0,0);
      glBegin(GL_TRIANGLES);
      glVertex3f(x,    y+0.2, z+0.3);
      glVertex3f(x+0.3,y+0.2, z-0.3);
      glVertex3f(x-0.3,y+0.2, z-0.3);
      glEnd();

      glBegin(GL_TRIANGLES);
      glVertex3f(x,    y+0.3, z+0.3);
      glVertex3f(x+0.3,y+0.3, z-0.3);
      glVertex3f(x-0.3,y+0.3, z-0.3);
      glEnd();


      glBegin(GL_QUADS);
      glVertex3f(x-0.3, y+0.3, z-0.3);
      glVertex3f(x-0.3, y+0.2, z-0.3);
      glVertex3f(x+0.3, y+0.2, z-0.3);
      glVertex3f(x+0.3, y+0.3, z-0.3);
      glEnd();

      glBegin(GL_QUADS);
      glVertex3f(x, y+0.3, z+0.3);
      glVertex3f(x, y+0.2, z+0.3);
      glVertex3f(x+0.3, y+0.2, z-0.3);
      glVertex3f(x+0.3, y+0.3, z-0.3);
      glEnd();

      glBegin(GL_QUADS);
      glVertex3f(x, y+0.3, z+0.3);
      glVertex3f(x, y+0.2, z+0.3);
      glVertex3f(x-0.3, y+0.2, z-0.3);
      glVertex3f(x-0.3, y+0.3, z-0.3);
      glEnd();



      // Perfilando los vertices
      ponerMaterial(0,0,0);
      // glBegin(GL_LINE_LOOP);
      // glVertex3f(x,    y+0.2, z+0.3);
      // glVertex3f(x+0.3,y+0.2, z-0.3);
      // glVertex3f(x-0.3,y+0.2, z-0.3);
      // glEnd();

      glBegin(GL_LINE_LOOP);
      glVertex3f(x,    y+0.3, z+0.3);
      glVertex3f(x+0.3,y+0.3, z-0.3);
      glVertex3f(x-0.3,y+0.3, z-0.3);
      glEnd();


      // glBegin(GL_LINE_LOOP);
      // glVertex3f(x-0.3, y+0.3, z-0.3);
      // glVertex3f(x-0.3, y+0.2, z-0.3);
      // glVertex3f(x+0.3, y+0.2, z-0.3);
      // glVertex3f(x+0.3, y+0.3, z-0.3);
      // glEnd();

      glBegin(GL_LINE_LOOP);
      glVertex3f(x, y+0.3, z+0.3);
      glVertex3f(x, y+0.2, z+0.3);
      glVertex3f(x+0.3, y+0.2, z-0.3);
      glVertex3f(x+0.3, y+0.3, z-0.3);
      glEnd();

      glBegin(GL_LINE_LOOP);
      glVertex3f(x, y+0.3, z+0.3);
      glVertex3f(x, y+0.2, z+0.3);
      glVertex3f(x-0.3, y+0.2, z-0.3);
      glVertex3f(x-0.3, y+0.3, z-0.3);
      glEnd();

      // Cuadrado para foto encima del quesito
      glBegin(GL_QUADS);
      glVertex3f(x-0.3, y+0.4, z);
      glVertex3f(x-0.3, y+0.7, z);
      glVertex3f(x+0.3, y+0.7, z);
      glVertex3f(x+0.3, y+0.4, z);
      glEnd();

}


void drawQuesitoDeEspaldas(double x, double y, double z){
      ponerMaterial(0,0,0);
      glBegin(GL_TRIANGLES);
      glVertex3f(x,    y+0.1, z-0.3);
      glVertex3f(x+0.3,y+0.1, z+0.3);
      glVertex3f(x-0.3,y+0.1, z+0.3);
      glEnd();

      ponerMaterial(1,0,0);
      glBegin(GL_TRIANGLES);
      glVertex3f(x,    y+0.2, z-0.3);
      glVertex3f(x+0.3,y+0.2, z+0.3);
      glVertex3f(x-0.3,y+0.2, z+0.3);
      glEnd();

      glBegin(GL_TRIANGLES);
      glVertex3f(x,    y+0.3, z-0.3);
      glVertex3f(x+0.3,y+0.3, z+0.3);
      glVertex3f(x-0.3,y+0.3, z+0.3);
      glEnd();


      glBegin(GL_QUADS);
      glVertex3f(x-0.3, y+0.3, z+0.3);
      glVertex3f(x-0.3, y+0.2, z+0.3);
      glVertex3f(x+0.3, y+0.2, z+0.3);
      glVertex3f(x+0.3, y+0.3, z+0.3);
      glEnd();

      glBegin(GL_QUADS);
      glVertex3f(x,     y+0.3, z-0.3);
      glVertex3f(x,     y+0.2, z-0.3);
      glVertex3f(x-0.3, y+0.2, z+0.3);
      glVertex3f(x-0.3, y+0.3, z+0.3);
      glEnd();

      glBegin(GL_QUADS);
      glVertex3f(x,     y+0.3, z-0.3);
      glVertex3f(x,     y+0.2, z-0.3);
      glVertex3f(x-0.3, y+0.2, z+0.3);
      glVertex3f(x-0.3, y+0.3, z+0.3);
      glEnd();



      // Perfilando los vertices
      ponerMaterial(0,0,0);
      // glBegin(GL_LINE_LOOP);
      // glVertex3f(x,    y+0.2, z-0.3);
      // glVertex3f(x+0.3,y+0.2, z+0.3);
      // glVertex3f(x-0.3,y+0.2, z+0.3);
      // glEnd();

      glBegin(GL_LINE_LOOP);
      glVertex3f(x,    y+0.3, z-0.3);
      glVertex3f(x+0.3,y+0.3, z+0.3);
      glVertex3f(x-0.3,y+0.3, z+0.3);
      glEnd();


      glBegin(GL_LINE_LOOP);
      glVertex3f(x-0.3, y+0.3, z+0.3);
      glVertex3f(x-0.3, y+0.2, z+0.3);
      glVertex3f(x+0.3, y+0.2, z+0.3);
      glVertex3f(x+0.3, y+0.3, z+0.3);
      glEnd();

      // glBegin(GL_LINE_LOOP);
      // glVertex3f(x,     y+0.3, z-0.3);
      // glVertex3f(x,     y+0.2, z-0.3);
      // glVertex3f(x-0.3, y+0.2, z+0.3);
      // glVertex3f(x-0.3, y+0.3, z+0.3);
      // glEnd();

      // glBegin(GL_LINE_LOOP);
      // glVertex3f(x,     y+0.3, z-0.3);
      // glVertex3f(x,     y+0.2, z-0.3);
      // glVertex3f(x-0.3, y+0.2, z+0.3);
      // glVertex3f(x-0.3, y+0.3, z+0.3);
      // glEnd();
}

void drawQuesitoDerecha(double x, double y, double z){
      ponerMaterial(0,0,0);
      glBegin(GL_TRIANGLES);
      glVertex3f(x-0.3, y+0.1, z+0.3);
      glVertex3f(x+0.3, y+0.1, z);
      glVertex3f(x-0.3, y+0.1, z-0.3);
      glEnd();

       ponerMaterial(1,0,0);
      glBegin(GL_TRIANGLES);
      glVertex3f(x-0.3, y+0.2, z+0.3);
      glVertex3f(x+0.3, y+0.2, z);
      glVertex3f(x-0.3, y+0.2, z-0.3);
      glEnd();

      glBegin(GL_TRIANGLES);
      glVertex3f(x-0.3, y+0.3, z+0.3);
      glVertex3f(x+0.3, y+0.3, z);
      glVertex3f(x-0.3, y+0.3, z-0.3);
      glEnd();


      glBegin(GL_QUADS);
      glVertex3f(x-0.3, y+0.3, z+0.3);
      glVertex3f(x-0.3, y+0.2, z+0.3);
      glVertex3f(x+0.3, y+0.2, z);
      glVertex3f(x+0.3, y+0.3, z);
      glEnd();

      glBegin(GL_QUADS);
      glVertex3f(x-0.3, y+0.3, z-0.3);
      glVertex3f(x-0.3, y+0.2, z-0.3);
      glVertex3f(x+0.3, y+0.2, z);
      glVertex3f(x+0.3, y+0.3, z);
      glEnd();

      glBegin(GL_QUADS);
      glVertex3f(x-0.3, y+0.3, z+0.3);
      glVertex3f(x-0.3, y+0.2, z+0.3);
      glVertex3f(x-0.3, y+0.2, z-0.3);
      glVertex3f(x-0.3, y+0.3, z-0.3);
      glEnd();



      // Perfilando los vertices
      ponerMaterial(0,0,0);

      glBegin(GL_LINE_LOOP);
      glVertex3f(x-0.3, y+0.3, z+0.3);
      glVertex3f(x-0.3, y+0.2, z+0.3);
      glVertex3f(x+0.3, y+0.2, z);
      glVertex3f(x+0.3, y+0.3, z);
      glEnd();

      glBegin(GL_LINE_LOOP);
      glVertex3f(x-0.3, y+0.3, z+0.3);
      glVertex3f(x-0.3, y+0.2, z+0.3);
      glVertex3f(x-0.3, y+0.2, z-0.3);
      glVertex3f(x-0.3, y+0.3, z-0.3);
      glEnd();
}



void drawQuesitoIzquierda(double x, double y, double z){
      ponerMaterial(0,0,0);
      glBegin(GL_TRIANGLES);
      glVertex3f(x+0.3, y+0.1, z+0.3);
      glVertex3f(x-0.3, y+0.1, z);
      glVertex3f(x+0.3, y+0.1, z-0.3);
      glEnd();

       ponerMaterial(1,0,0);
      glBegin(GL_TRIANGLES);
      glVertex3f(x+0.3, y+0.2, z+0.3);
      glVertex3f(x-0.3, y+0.2, z);
      glVertex3f(x+0.3, y+0.2, z-0.3);
      glEnd();

      glBegin(GL_TRIANGLES);
      glVertex3f(x+0.3, y+0.3, z+0.3);
      glVertex3f(x-0.3, y+0.3, z);
      glVertex3f(x+0.3, y+0.3, z-0.3);
      glEnd();


      glBegin(GL_QUADS);
      glVertex3f(x+0.3, y+0.3, z+0.3);
      glVertex3f(x+0.3, y+0.2, z+0.3);
      glVertex3f(x-0.3, y+0.2, z);
      glVertex3f(x-0.3, y+0.3, z);
      glEnd();

      glBegin(GL_QUADS);
      glVertex3f(x+0.3, y+0.3, z-0.3);
      glVertex3f(x+0.3, y+0.2, z-0.3);
      glVertex3f(x-0.3, y+0.2, z);
      glVertex3f(x-0.3, y+0.3, z);
      glEnd();

      glBegin(GL_QUADS);
      glVertex3f(x+0.3, y+0.3, z+0.3);
      glVertex3f(x+0.3, y+0.2, z+0.3);
      glVertex3f(x+0.3, y+0.2, z-0.3);
      glVertex3f(x+0.3, y+0.3, z-0.3);
      glEnd();



      // Perfilando los vertices
      ponerMaterial(0,0,0);
      glBegin(GL_LINE_LOOP);
      glVertex3f(x+0.3, y+0.3, z+0.3);
      glVertex3f(x+0.3, y+0.2, z+0.3);
      glVertex3f(x-0.3, y+0.2, z);
      glVertex3f(x-0.3, y+0.3, z);
      glEnd();


      glBegin(GL_LINE_LOOP);
      glVertex3f(x+0.3, y+0.3, z+0.3);
      glVertex3f(x+0.3, y+0.2, z+0.3);
      glVertex3f(x+0.3, y+0.2, z-0.3);
      glVertex3f(x+0.3, y+0.3, z-0.3);
      glEnd();

}


void drawPersonaje(double x, double y, double z, bool deCara, int colorPelo, int colorCamisa, int colorPantalon, const std::string & texturaCara){
  
  
  //Sombra
  ponerMaterial(0,0,0);
  drawCube(x,y+0.1,z,0.25,0);

  // Cabeza
  switch (colorPelo){
    case 0: // Negro
            ponerMaterial(0,0,0);
            break;
    case 1: // Blanco
            ponerMaterial(1,1,1);
            break;
    case 2: // Rubio
            ponerMaterial(0.95,0.66,0);
            break;
    case 3: // Pelirrojo
            ponerMaterial(0.68,0.17,0.12);
            break;
    case 4: // Azul
            ponerMaterial(0.01,0.22,0.44);
            break;
    case 5: // Rosa
            ponerMaterial(0.85,0.3,0.54);
            break;
  }
  drawCube(x,y+0.5,z,0.14,0.14);
  


  // Cara
  if (deCara){
    ponerMaterial(0.65,0.37,0.18);
    drawCube(x,y+0.47,z,0.14,0.14);
    // // Ojo izquierdo
    // ponerMaterial(0,0,0);
    // glBegin(GL_QUADS);
    //   glVertex3f(x-0.03,y+0.57,z+0.08);
    //   glVertex3f(x-0.03,y+0.58,z+0.08);
    //   glVertex3f(x-0.02,y+0.58,z+0.08);
    //   glVertex3f(x-0.02,y+0.57,z+0.08);
    // glEnd();

    // // Ojo derecho
    // ponerMaterial(0,0,0);
    // glBegin(GL_QUADS);
    //   glVertex3f(x+0.03,y+0.57,z+0.08);
    //   glVertex3f(x+0.03,y+0.58,z+0.08);
    //   glVertex3f(x+0.02,y+0.58,z+0.08);
    //   glVertex3f(x+0.02,y+0.57,z+0.08);
    // glEnd();

    // // Boca
    // ponerMaterial(0.63,0.14,0.11);
    // glBegin(GL_QUADS);
    //   glVertex3f(x+0.03,y+0.53,z+0.08);
    //   glVertex3f(x+0.03,y+0.54,z+0.08);
    //   glVertex3f(x-0.03,y+0.54,z+0.08);
    //   glVertex3f(x-0.03,y+0.53,z+0.08);
    // glEnd();

    Retrato3D cara = Retrato3D(texturaCara);
    cara.setPosicion(_vertex3<float>(x-0.07,y+0.5,z+0.08));
    cara.setTranformacion(_vertex4<float>(Escalado_,0.14,0.14,0.14));
    cara.draw(1);
  }


  switch (colorCamisa){
    case 0: // Negro
            // Pecho
            ponerMaterial(0,0,0);
            drawCube(x,y+0.35,z,0.16,0.15);
            // Brazo izquierdo
            ponerMaterial(0,0,0);
            drawCube(x-0.1,y+0.35,z,0.05,0.15);
            // Brazo derecho
            ponerMaterial(0,0,0);
            drawCube(x+0.1,y+0.35,z,0.05,0.15);
            break;
    case 1: // Blanco
            // Pecho
            ponerMaterial(1,1,1);
            drawCube(x,y+0.35,z,0.16,0.15);
            // Brazo izquierdo
            ponerMaterial(1,1,1);
            drawCube(x-0.1,y+0.35,z,0.05,0.15);
            // Brazo derecho
            ponerMaterial(1,1,1);
            drawCube(x+0.1,y+0.35,z,0.05,0.15);
            break;
    case 2: // Rubio
            // Pecho
            ponerMaterial(0.95,0.66,0);
            drawCube(x,y+0.35,z,0.16,0.15);
            // Brazo izquierdo
            ponerMaterial(0.95,0.66,0);
            drawCube(x-0.1,y+0.35,z,0.05,0.15);
            // Brazo derecho
            ponerMaterial(0.95,0.66,0);
            drawCube(x+0.1,y+0.35,z,0.05,0.15);
            break;
    case 3: // Pelirrojo
            // Pecho
            ponerMaterial(0.68,0.17,0.12);
            drawCube(x,y+0.35,z,0.16,0.15);
            // Brazo izquierdo
            ponerMaterial(0.68,0.17,0.12);
            drawCube(x-0.1,y+0.35,z,0.05,0.15);
            // Brazo derecho
            ponerMaterial(0.68,0.17,0.12);
            drawCube(x+0.1,y+0.35,z,0.05,0.15);
            break;
    case 4: // Azul
            // Pecho
            ponerMaterial(0.01,0.22,0.44);
            drawCube(x,y+0.35,z,0.16,0.15);
            // Brazo izquierdo
            ponerMaterial(0.01,0.22,0.44);
            drawCube(x-0.1,y+0.35,z,0.05,0.15);
            // Brazo derecho
            ponerMaterial(0.01,0.22,0.44);
            drawCube(x+0.1,y+0.35,z,0.05,0.15);
            break;
    case 5: // Rosa
            // Pecho
            ponerMaterial(0.85,0.3,0.54);
            drawCube(x,y+0.35,z,0.16,0.15);
            // Brazo izquierdo
            ponerMaterial(0.85,0.3,0.54);
            drawCube(x-0.1,y+0.35,z,0.05,0.15);
            // Brazo derecho
            ponerMaterial(0.85,0.3,0.54);
            drawCube(x+0.1,y+0.35,z,0.05,0.15);
            break;
  }
  // Mano izquierda
  ponerMaterial(0.65,0.37,0.18);
  drawCube(x-0.1,y+0.30,z,0.045,0.05);  
  // Mano derecha
  ponerMaterial(0.65,0.37,0.18);
  drawCube(x+0.1,y+0.30,z,0.045,0.05);  

  switch(colorPantalon){
    case 0: // Negro
            // Cintura
            ponerMaterial(0,0,0);
            drawCube(x,y+0.25,z,0.16,0.1);
            // Pierna izquierda
            ponerMaterial(0,0,0);
            drawCube(x-0.045,y+0.11,z,0.08,0.15);
            // Pierna derecha
            ponerMaterial(0,0,0);
            drawCube(x+0.045,y+0.11,z,0.08,0.15);
            break;
    case 1: // Blanco
            // Cintura
            ponerMaterial(1,1,1);
            drawCube(x,y+0.25,z,0.16,0.1);
            // Pierna izquierda
            ponerMaterial(1,1,1);
            drawCube(x-0.045,y+0.11,z,0.08,0.15);
            // Pierna derecha
            ponerMaterial(1,1,1);
            drawCube(x+0.045,y+0.11,z,0.08,0.15);
            break;
    case 2: // Rubio
            // Cintura
            ponerMaterial(0.95,0.66,0);
            drawCube(x,y+0.25,z,0.16,0.1);
            // Pierna izquierda
            ponerMaterial(0.95,0.66,0);
            drawCube(x-0.045,y+0.11,z,0.08,0.15);
            // Pierna derecha
            ponerMaterial(0.95,0.66,0);
            drawCube(x+0.045,y+0.11,z,0.08,0.15);
            break;
    case 3: // Pelirrojo
            // Cintura
            ponerMaterial(0.68,0.17,0.12);
            drawCube(x,y+0.25,z,0.16,0.1);
            // Pierna izquierda
            ponerMaterial(0.68,0.17,0.12);
            drawCube(x-0.045,y+0.11,z,0.08,0.15);
            // Pierna derecha
            ponerMaterial(0.68,0.17,0.12);
            drawCube(x+0.045,y+0.11,z,0.08,0.15);
            break;    
    case 4: // Azul vaquero
            // Cintura
            ponerMaterial(0.01,0.22,0.44);
            drawCube(x,y+0.25,z,0.16,0.1);
            // Pierna izquierda
            ponerMaterial(0.01,0.22,0.44);
            drawCube(x-0.045,y+0.11,z,0.08,0.15);
            // Pierna derecha
            ponerMaterial(0.01,0.22,0.44);
            drawCube(x+0.045,y+0.11,z,0.08,0.15);
            break;    
    case 5: // Rosa
            // Cintura
            ponerMaterial(0.85,0.3,0.54);
            drawCube(x,y+0.25,z,0.16,0.1);
            // Pierna izquierda
            ponerMaterial(0.85,0.3,0.54);
            drawCube(x-0.045,y+0.11,z,0.08,0.15);
            // Pierna derecha
            ponerMaterial(0.85,0.3,0.54);
            drawCube(x+0.045,y+0.11,z,0.08,0.15);
            break;    
  }
  // Pie izquierdo
  ponerMaterial(0.15,0.15,0.15);
  drawCube(x-0.045,y+0.1,z,0.08,0.01);
  // Pie derecho
  ponerMaterial(0.15,0.15,0.15);
  drawCube(x+0.045,y+0.1,z,0.08,0.01);

}


void drawDog(double x, double y, double z){
  // sombra


  ponerMaterial(0,0,0);
  drawCube(x, y+0.1, z, 0.5, 0.0);

  // tronco
  ponerMaterial(0.76,0.68,0.47);
  drawCube(x, y+0.25, z-0.45, 0.30, 0.15);

  ponerMaterial(0.76,0.68,0.47);
  drawCube(x, y+0.25, z-0.15, 0.30, 0.15);

  ponerMaterial(0.76,0.68,0.47);
  drawCube(x, y+0.25, z+0.15, 0.30, 0.15);



  // patas

  ponerMaterial(0.76,0.68,0.47);
  drawCube(x-0.10, y+0.1, z-0.55, 0.1, 0.15);

  ponerMaterial(0.76,0.68,0.47);
  drawCube(x+0.10, y+0.1, z-0.55, 0.1, 0.15);

  ponerMaterial(0.76,0.68,0.47);
  drawCube(x-0.10, y+0.1, z+0.25, 0.1, 0.15);

  ponerMaterial(0.76,0.68,0.47);
  drawCube(x+0.10, y+0.1, z+0.25, 0.1, 0.15);

  // cabeza

  ponerMaterial(0.76,0.68,0.47);
  drawCube(x, y+0.4, z+0.25, 0.15, 0.15);

    // Ojo izquierdo
    ponerMaterial(0,0,0);
    glBegin(GL_QUADS);
      glVertex3f(x-0.03,y+0.50,z+0.05);
      glVertex3f(x-0.03,y+0.52,z+0.05);
      glVertex3f(x-0.02,y+0.52,z+0.05);
      glVertex3f(x-0.02,y+0.50,z+0.05);
    glEnd();

    // Ojo derecho
    ponerMaterial(0,0,0);
    glBegin(GL_QUADS);
      glVertex3f(x+0.03,y+0.50,z+0.05);
      glVertex3f(x+0.03,y+0.52,z+0.05);
      glVertex3f(x+0.02,y+0.52,z+0.05);
      glVertex3f(x+0.02,y+0.50,z+0.05);
    glEnd();

  ponerMaterial(0,0,0);
  drawCube(x, y+0.42, z+0.32, 0.05, 0.05);



}




void drawPlayer(double x, double y, double z, char pos){
  switch(pos){
    case '0':
        drawQuesitoDeFrente(x,y,z);
        break;
    case '1':
        drawQuesitoDeEspaldas(x,y,z);
        break;
    case '2':
        drawQuesitoIzquierda(x,y,z);
        break;
    case '3':
        drawQuesitoDerecha(x,y,z);
        break;
  }
}

void drawGenericObject(double x, double y, double z){
  // Objeto generico
  ponerMaterial(0,0,0);
  drawCube(x,y+0.101,z,0.2,0);

  ponerMaterial(0.85,0.3,0.54); 
  drawCube(x,y+0.4, z,0.2,0.1);
}

