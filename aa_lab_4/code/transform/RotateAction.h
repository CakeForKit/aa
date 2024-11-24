#pragma once

#include "TransformAction.h"

enum class Axis {
    OX, OY, OZ
} ;

// вращение только вокур оси OY
class RotateAction : public TransformAction
{
public:
    RotateAction(float angle_grad, Point3 &&center, Axis axis);
};
