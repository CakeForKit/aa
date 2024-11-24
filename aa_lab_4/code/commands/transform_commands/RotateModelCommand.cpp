#include "RotateModelCommand.h"

RotateModelCommand::RotateModelCommand(size_t _idModel, float _angle_grad)
: idModel(_idModel), angle_grad(_angle_grad) {}

void RotateModelCommand::execute() {
    PtrObjectScene model = sceneManager->getModel(idModel);
    transformManager->rotateModel(model, angle_grad);

    std::cout << "Rotated model:\n" << *model;
}