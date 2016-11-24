#include"luz.hpp"
#include"vertex.h"
#include <cmath>

void Luz::draw(){
    if(encendida==true){
        GLfloat posL[4] = {1.0,1.0,1.0,1.0};
        GLfloat ambi[4] = {0.6,0.6,0.6,1.0};
        GLfloat diff[4] = {0.2,0.2,0.2,1.0};
        GLfloat spec[4] = {0.5,0.5,0.5,1.0};
        glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER,GL_TRUE);
        glLightfv(nLuz,GL_POSITION,posL);
        glLightfv(nLuz,GL_AMBIENT,ambi);
        glLightfv(nLuz,GL_DIFFUSE,diff);
        glLightfv(nLuz,GL_SPECULAR,spec);
        glEnable(nLuz);
    }
    else{
        glDisable(nLuz);
    }
}
