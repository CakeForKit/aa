#pragma once

#include "ReaderSolution.h"
#include "DirectorSolution.h"
#include "ObjectScene.h"
#include <assert.h>

class LoadManager
{
protected:
    ReaderSolution readerSolution;
    DirectorSolution directorSolution;

public:
    LoadManager();

    std::shared_ptr<ObjectScene> loadModelFromFile(idReaderCreator id_reader, 
                                                    idDirectorCreator id_director, 
                                                    const char *filename, 
                                                    size_t stepOfRevolving,
                                                    std::shared_ptr<Material> material);
};
