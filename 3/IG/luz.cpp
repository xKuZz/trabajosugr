#include "luz.h"


//*************************************************************************
// FUENTE DE LUZ(CLASE ABSTRACTA)
//*************************************************************************
LightSource::LightSource(GLenum id, const RGBAColor& ambiente, const RGBAColor &difuso, const RGBAColor &especular)
    : id(id), ambiente(ambiente),difuso(difuso), especular(especular) {}

void LightSource::enable()
{ // Activamos la fuente y configuramos colores
    glEnable(GL_LIGHTING);
    glEnable(id);
    glLightfv(id,GL_AMBIENT, ambiente.data());
    glLightfv(id,GL_DIFFUSE, difuso.data());
    glLightfv(id, GL_SPECULAR, especular.data());
}

void LightSource::disable() const
{
    glDisable(id);
}

LightSource::Type LightSource::getType() const
{
    return type;
}

//*************************************************************************
// FUENTE DE LUZ POSICIONAL
//*************************************************************************
PositionalLightSource::PositionalLightSource(GLenum id, const RGBAColor& ambiente, const RGBAColor &difuso, const RGBAColor &especular, const std::array<float, 3>& pos)
    : LightSource(id, ambiente, difuso, especular)
{
    type = Type::Positional;
    position[0] = pos[0];
    position[1] = pos[1];
    position[2] = pos[2];
    position[3] = 1.0;
}
#include <iostream>
void PositionalLightSource::enable()
{ // Ponemos fuente en posición
    LightSource::enable();
    glLightfv(id, GL_POSITION, position.data());
}

//*************************************************************************
// FUENTE DE LUZ DIRECCIONAL
//*************************************************************************
DirectionalLightSource::DirectionalLightSource(GLenum id, const RGBAColor& ambiente, const RGBAColor &difuso, const RGBAColor &especular, const std::array<float, 3>& pos, double alpha, double beta)
    : LightSource(id, ambiente, difuso, especular)
{
    type = Type::Directional;
    position[0] = pos[0];
    position[1] = pos[1];
    position[2] = pos[2];
    position[3] = 0.0;
    this->alpha = alpha;
    this->beta = beta;
}

void DirectionalLightSource::enable()
{
    LightSource::enable();
    glPushMatrix();
        glRotatef(alpha,0,1,0);
        glRotatef(beta,1,0,0);
        glLightfv(id, GL_POSITION, position.data());
    glPopMatrix();
}

void DirectionalLightSource::modifyAlpha(float value)
{

    alpha += value;
    if (alpha > 360)
        alpha -= 360;
    if (alpha < -360)
        alpha += 360;

}

void DirectionalLightSource::modifyBeta(float value)
{
    beta += value;

    if (beta > 360)
        beta -= 360;
    if (beta < -360)
        beta += 360;
}

