#pragma once

#include "TransformAction.h"

class MoveAction : public TransformAction
{
public:
    MoveAction(double dx, double dy, double dz);
};
