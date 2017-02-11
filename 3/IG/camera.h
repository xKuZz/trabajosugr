#ifndef CAMERA_H
#define CAMERA_H
#include <array>
#include <GL/glut.h>

class Camera
{
public:
    enum class Type {Orthogonal, Perspective};
    Camera(const Type& type, const std::array<GLdouble, 6>& projection, const std::array<GLdouble, 9>& look);

    void applyProjection() const;
    Type getType() const;
    void setViewer() const;
    void goForwardViewer();
    void goBackwardViewer();
    void goRightViewer();
    void goLeftViewer();
    void resetViewer();
    void turn(int x, int y);

private:
    void applyAsOrthogonal() const;
    void applyAsPerspective() const;
    GLdouble top;
    GLdouble bottom;
    GLdouble left;
    GLdouble right;
    GLdouble nearVal;
    GLdouble farVal;
    Type type;
    GLdouble eyeX;
    GLdouble eyeY;
    GLdouble eyeZ;
    GLdouble centerX;
    GLdouble centerY;
    GLdouble centerZ;
    GLdouble upX;
    GLdouble upY;
    GLdouble upZ;
    GLdouble saveEyeX;
    GLdouble saveEyeY;
    GLdouble saveEyeZ;


};

#endif // CAMERA_H
