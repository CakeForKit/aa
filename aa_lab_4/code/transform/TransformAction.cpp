#include "TransformAction.h"

TransformAction::TransformAction() : mat(Matrix4()) {}

void TransformAction::transform(psPoint3 p) const {
    *p = mat * (*p); 
}

Point3 TransformAction::transform(Point3 p) const {
    return mat * p; 
}

void TransformAction::addAction(std::shared_ptr<TransformAction> action) {
    mat *= action->getMatrix();
}

Matrix4 &TransformAction::getMatrix() {
    return mat;
}