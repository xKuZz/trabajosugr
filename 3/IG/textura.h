#ifndef TEXTURA_H
#define TEXTURA_H
#include <GL/glut.h>
#include <QImage>
#include <array>
#include <iostream>

struct Texel {
    double s, t;
    Texel(double s, double t) : s(s), t(t) {}
};

class Texture
{
public:
    Texture(const QString& rute, bool automatic = true);

    void enable() const;
    static void disable();
    void setPlanes(const std::array<float, 4> &s,
                   const std::array<float, 4> &t);

    GLuint getId() const;

private:
    QImage image;
    bool generate;
    std::array<float, 4> planeS;
    std::array<float, 4> planeT;
    GLuint id;
};

#endif // TEXTURA_H
