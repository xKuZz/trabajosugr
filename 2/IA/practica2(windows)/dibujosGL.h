#ifndef DIBUJOSGL_H__
#define DIBUJOSGL_H__

#include "include/GL/glui.h"
#include <cstdlib>
#include <iostream>
#include <string.h>
 

 using namespace std;

// Figuras 3D openGL
void drawCube(double x, double y, double z, double base, double alto); 
void drawTree(double x, double y, double z, double base, double alto);
void drawWall(double x, double y, double z, double base, double alto);
void drawQuesitoDeFrente(double x, double y, double z);
void drawQuesitoDeEspaldas(double x, double y, double z);
void drawQuesitoDerecha(double x, double y, double z);
void drawQuesitoIzquierda(double x, double y, double z);
void drawPersonaje(double x, double y, double z, bool deCara, int colorPelo, int colorCamisa, int colorPantalon, const std::string & texturaCara);
void drawDog(double x, double y, double z);
void drawPlayer(double x, double y, double z, char pos);
void drawGenericObject(double x, double y, double z);
void ponerMaterial(float R, float G, float B);



#endif