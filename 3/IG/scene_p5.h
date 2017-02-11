#ifndef SCENE_P5_H
#define SCENE_P5_H
#include <array>
#include <vector>
#include "camera.h"
#include "rgb.h"

class Scene_p5
{
public:
    Scene_p5();
    Camera *getCurrentCamera() const;
    void changeCamera(int idx);

private:
    std::vector<Camera> cameras;
    Camera* currentCamera;

};

#endif // SCENE_P5_H
