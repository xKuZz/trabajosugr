#include "camera.h"

Camera::Camera(const Camera::Type &type, const std::array<GLdouble, 6> &projection, const std::array<GLdouble, 9> &look)
{
    this->type    = type;
    this->left    = projection[0];
    this->right   = projection[1];
    this->bottom  = projection[2];
    this->top     = projection[3];
    this->nearVal = projection[4];
    this->farVal  = projection[5];
    this->eyeX    = look[0];
    this->eyeY    = look[1];
    this->eyeZ    = look[2];
    this->centerX = look[3];
    this->centerY = look[4];
    this->centerZ = look[5];
    this->upX     = look[6];
    this->upY     = look[7];
    this->upZ     = look[8];
    this->saveEyeX = eyeX;
    this->saveEyeY = eyeY;
    this->saveEyeZ = eyeZ;
}

void Camera::applyProjection() const
{
    if (type == Type::Orthogonal)
        applyAsOrthogonal();
    else
        applyAsPerspective();
}

void Camera::applyAsOrthogonal() const
{
    glOrtho(left,right,bottom,top,nearVal,farVal);
}

void Camera::applyAsPerspective() const
{
    glFrustum(left,right,bottom,top,nearVal,farVal);
}

Camera::Type Camera::getType() const
{
    return type;
}

void Camera::setViewer() const
{
    gluLookAt(eyeX, eyeY, eyeZ, centerX, centerY, centerZ, upX, upY, upZ);
}

void Camera::goForwardViewer()
{
    eyeZ -= 1.0;
}

void Camera::goBackwardViewer()
{
    eyeZ += 1.0;
}

void Camera::goRightViewer()
{
    eyeX += 1.0;
}

void Camera::goLeftViewer()
{
    eyeX -= 1.0;
}

void Camera::resetViewer()
{
    eyeX = saveEyeX;
    eyeY = saveEyeY;
    eyeZ = saveEyeZ;
}

void Camera::turn(int x, int y)
{
    centerX += x;
    centerY += y;
}
