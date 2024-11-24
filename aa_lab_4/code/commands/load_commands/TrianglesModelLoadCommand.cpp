#include "TrianglesModelLoadCommand.h"

TrianglesModelLoadCommand::TrianglesModelLoadCommand(const char *_filename, size_t _stepOfRevolving, idMaterial _id_material) 
: BaseLoadCommand(_id_material), filename(_filename), stepOfRevolving(_stepOfRevolving) { 
    id_director = idDirectorCreator::TRIANGLES; 
    id_reader = idReaderCreator::TRIANGLES;
}
    
void TrianglesModelLoadCommand::execute() {
    std::shared_ptr<Material> material = materialManager->getMaterial(id_material);
    PtrObjectScene model = loadManager->loadModelFromFile(id_reader, id_director, filename, stepOfRevolving, material);

    sceneManager->addModel(model);
}