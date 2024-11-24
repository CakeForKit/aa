#include "LoadManager.h"


LoadManager::LoadManager() {
    bool rv;
    rv = readerSolution.registrate(idReaderCreator::TRIANGLES, std::make_shared<TrianglesModelReaderCreator_t>());
    assert(rv);
    rv = directorSolution.registrate(idDirectorCreator::TRIANGLES, std::make_shared<TrianglesModelDirectorCreator_t>());
    assert(rv);
}

std::shared_ptr<ObjectScene> LoadManager::loadModelFromFile(idReaderCreator id_reader, 
                                                            idDirectorCreator id_director, 
                                                            const char *filename, 
                                                            size_t stepOfRevolving,
                                                            std::shared_ptr<Material> material) {

    std::shared_ptr<BaseReaderCreator> readerCreator(readerSolution.create(id_reader));
    std::shared_ptr<TrianglesModelReaderCreator_t> trinaglesModelReaderCreator  = std::dynamic_pointer_cast<TrianglesModelReaderCreator_t>(readerCreator);
    assert(trinaglesModelReaderCreator != nullptr);

    std::shared_ptr<VolumeModelReader> reader = trinaglesModelReaderCreator->createReader(filename, stepOfRevolving); //std::make_shared<TrianglesModelReader>("/home/kathrine/cg_cp/data/test_model_1.txt");
    

    std::shared_ptr<BaseDirectorCreator> directorCreator(directorSolution.create(id_director));
    std::shared_ptr<TrianglesModelDirectorCreator_t> trianglesModelDirectorCreator = std::dynamic_pointer_cast<TrianglesModelDirectorCreator_t>(directorCreator);
    assert(trianglesModelDirectorCreator != nullptr);
    
    std::shared_ptr<VolumeModelDirector> director = trianglesModelDirectorCreator->createDirector(reader, material);
    return director->get();
}
