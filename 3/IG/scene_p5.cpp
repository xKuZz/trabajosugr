#include "scene_p5.h"

Scene_p5::Scene_p5()
{
    std::array<GLdouble, 6> proj{-5,5,-5,5,10,1000};
    std::array<GLdouble, 9> pointOfView{0,0,15,0,0,0,0,1,0};
    cameras.emplace_back(Camera::Type::Perspective, proj, pointOfView);
    pointOfView[2] = 0;
    pointOfView[0] = 15;
    cameras.emplace_back(Camera::Type::Orthogonal, proj, pointOfView);
    pointOfView[2] = 0;
    pointOfView[0] = 0.1;
    pointOfView[1] = 25;
    cameras.emplace_back(Camera::Type::Orthogonal, proj, pointOfView);
    currentCamera = &cameras.front();
}

Camera *Scene_p5::getCurrentCamera() const
{
    return currentCamera;
}

void Scene_p5::changeCamera(int idx)
{
    currentCamera = &cameras[idx];
}
