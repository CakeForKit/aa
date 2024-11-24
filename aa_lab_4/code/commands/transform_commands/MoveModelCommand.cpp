#include "MoveModelCommand.h"

MoveModelCommand::MoveModelCommand(size_t _idModel, double _dx, double _dy, double _dz)
: idModel(_idModel), dx(_dx), dy(_dy), dz(_dz) {}

void MoveModelCommand::execute() {
    PtrObjectScene model = sceneManager->getModel(idModel);
    transformManager->moveModel(model, dx, dy, dz);

    // std::cout << "Moved model:\n" << *model;
}