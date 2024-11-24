#pragma once

#include "BaseCommand.h"
#include "LoadManager.h"

class BaseLoadCommand : public BaseCommand 
{
protected:
    idReaderCreator id_reader;
    idDirectorCreator id_director;
    idMaterial id_material;

public:
    BaseLoadCommand(idMaterial _id_material);
    virtual ~BaseLoadCommand() = 0;

    idReaderCreator getReaderId();
    idDirectorCreator getDirectorId();

    virtual void execute() = 0;
};