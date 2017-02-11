#include "material.h"

Material::Material(RGBColor ambient, RGBColor diffuse, RGBColor specular, double bright, Texture* tex)
    : ambient(ambient), diffuse(diffuse), specular(specular), brightExponent(bright), tex(tex)
{

}

void Material::enable()
{
    glEnable(GL_LIGHTING);

        glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
        glPolygonMode(GL_FRONT,GL_FILL);
        glMaterialfv(GL_FRONT,  GL_AMBIENT,  ambient.data());
        glMaterialfv(GL_FRONT,  GL_DIFFUSE,  diffuse.data());
        glMaterialfv(GL_FRONT, GL_SPECULAR, specular.data());
        glMaterialf(GL_FRONT, GL_SHININESS, brightExponent*128);

    if (tex)
        tex->enable();
    else
        Texture::disable();
}
