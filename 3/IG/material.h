#ifndef MATERIAL_H
#define MATERIAL_H
#include "textura.h"
#include "rgb.h"

/** @brief Un material es un conjunto de valores asociado a los parámetros de iluminación de OpenGL para un objeto concreto
 */
class Material
{
public:
    Material() {}
    Material(RGBColor ambient, RGBColor diffuse, RGBColor specular, double bright, Texture* tex = nullptr);
    void enable();
private:
    RGBAColor ambient;
    RGBAColor diffuse;
    RGBAColor specular;
    double brightExponent;
    Texture* tex;

};

#endif // MATERIAL_H
