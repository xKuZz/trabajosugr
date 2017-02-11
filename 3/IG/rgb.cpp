#include "rgb.h"

RGBColor::RGBColor()
{

}

RGBColor::RGBColor(float r, float g, float b)
 {
    color[0] = r;
    color[1] = g;
    color[2] = b;
}

void RGBColor::applyColor() const
{
    glColor3fv(&color[0]);
}

const float *RGBColor::data() const
{
    return &color[0];
}

float RGBColor::getR() const
{
    return color[0];
}


float RGBColor::getG() const
{
    return color[1];
}

float RGBColor::getB() const
{
    return color[2];
}


RGBAColor::RGBAColor(const RGBColor &col)
{
    color[0] = col.getR();
    color[1] = col.getG();
    color[2] = col.getB();
    color[3] = 1.0;
}

RGBAColor::RGBAColor(float r, float g, float b, float a)
{
    color[0] = r;
    color[1] = g;
    color[2] = b;
    color[3] = a;
}

const float *RGBAColor::data() const
{
    return &color[0];
}

float RGBAColor::getR() const
{
    return color[0];
}

float RGBAColor::getG() const
{
    return color[1];
}

float RGBAColor::getB() const
{
    return color[2];
}

float RGBAColor::getA() const
{
    return color[3];
}
