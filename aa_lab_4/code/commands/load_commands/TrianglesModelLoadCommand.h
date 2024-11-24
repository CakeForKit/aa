#pragma once

#include "BaseLoadCommand.h"

class TrianglesModelLoadCommand : public BaseLoadCommand
{
protected:
    const char *filename;
    size_t stepOfRevolving;

public:
    TrianglesModelLoadCommand() = delete;
    TrianglesModelLoadCommand(const char *_filename, size_t _stepOfRevolving, idMaterial _id_material);

    virtual void execute();
};
