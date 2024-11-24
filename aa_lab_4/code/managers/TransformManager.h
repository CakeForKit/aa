#pragma once

#include "ObjectScene.h"
#include "Camera.h"
#include "MoveAction.h"
#include "RotateAction.h"

class TransformManager
{
public:
    void moveModel(PtrObjectScene model, double dx, double dy, double dz);
    void rotateModel(PtrObjectScene model, float angle);

    // void moveCamera(std::shared_ptr<Camera> camera, double dx, double dy, double dz)
    void rotateCamera(std::shared_ptr<Camera> camera, float angle, Axis axis);
};
