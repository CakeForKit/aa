#include "MoveAction.h"

MoveAction::MoveAction(double dx, double dy, double dz) {
    mat = Matrix4(glm::translate(glm::mat4(1.0f), glm::vec3(dx, dy, dz)));
}