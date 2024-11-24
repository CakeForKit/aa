#pragma once

#include "TransformCommand.h"

class RotateCameraCommand : public TransformCommand
{
protected:
    float angle_grad;
    Axis axis;

public:
    RotateCameraCommand() = delete;
    RotateCameraCommand(float _angle_grad, Axis _axis);

    virtual void execute();
};
