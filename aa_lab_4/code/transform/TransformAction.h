#pragma once

#include "Matrix4.h"
#include "Vector3.h"

class TransformAction
{
protected:
    Matrix4 mat;

public:
    TransformAction();

    void transform(psPoint3 p) const;
    Point3 transform(Point3 p) const;

    void addAction(std::shared_ptr<TransformAction> action);

    Matrix4 &getMatrix();
};
