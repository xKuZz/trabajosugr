#include "textura.h"
Texture::Texture(const QString& rute, bool automatic)
    :  generate(automatic)
{
    if (!image.load(rute))
        std::cerr << "Error al leer la imagen " << rute.toStdString() << '\n';
    image = image.mirrored(true,true);
    glGenTextures(1, &id);
    glBindTexture(GL_TEXTURE_2D, id);
    // Crear textura
    glTexImage2D(GL_TEXTURE_2D,0,4,image.width(),image.height(),0,GL_BGRA_EXT,GL_UNSIGNED_BYTE,image.bits());
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::enable() const
{
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, id);
    if (generate) {
        glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
        glTexGenfv(GL_S, GL_OBJECT_PLANE, planeS.data());
        glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
        glTexGenfv(GL_T, GL_OBJECT_PLANE, planeT.data());
        glEnable(GL_TEXTURE_GEN_S);
        glEnable(GL_TEXTURE_GEN_T);
    }
    else {
        glDisable(GL_TEXTURE_GEN_S);
        glDisable(GL_TEXTURE_GEN_T);
    }
}

void Texture::disable()
{
    glDisable(GL_TEXTURE_2D);
}

void Texture::setPlanes(const std::array<float, 4> &s, const std::array<float, 4> &t)
{
    planeS = s;
    planeT = t;
}

GLuint Texture::getId() const
{
    return id;
}
