#pragma once
#include "TransformCommand.h"

class RotateModelCommand : public TransformCommand
{
protected:
    size_t idModel;
    float angle_grad;

public:
    RotateModelCommand() = delete;
    RotateModelCommand(size_t _idModel, float _angle_grad);

    virtual void execute();
};
