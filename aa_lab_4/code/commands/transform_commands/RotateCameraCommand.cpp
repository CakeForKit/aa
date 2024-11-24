#include "RotateCameraCommand.h"

RotateCameraCommand::RotateCameraCommand(float _angle_grad, Axis _axis)
: angle_grad(_angle_grad), axis(_axis) {}

void RotateCameraCommand::execute() {
    std::shared_ptr<Camera> camera = sceneManager->getActiveCamera();

    std::cout << "\nBefore camera:\n" << *camera;

    transformManager->rotateCamera(camera, angle_grad, axis);

    // std::cout << "Rotated camera:\n" << *camera;
}