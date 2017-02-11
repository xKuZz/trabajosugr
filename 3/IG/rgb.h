#ifndef RGB_H
#define RGB_H
#include <GL/glut.h>
#include <iostream>

class RGBColor
{
public:
    RGBColor();
    RGBColor(float r, float g, float b);
    void applyColor() const;
    const float* data() const;
    float getR() const;
    float getG() const;
    float getB() const;

private:
    float color[3];
};

class RGBAColor {
public:
    RGBAColor() = default;
    RGBAColor(const RGBColor& col);
    RGBAColor(float r, float g, float b, float a = 1.0);
    const float* data() const;
    float getR() const;
    float getG() const;
    float getB() const;
    float getA() const;
private:
    float color[4];
};

#endif // RGB_H
