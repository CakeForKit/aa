#include "BaseLoadCommand.h"

BaseLoadCommand::BaseLoadCommand(idMaterial _id_material)
: id_material(_id_material) {}

BaseLoadCommand::~BaseLoadCommand() = default;

idReaderCreator BaseLoadCommand::getReaderId() { return id_reader; }

idDirectorCreator BaseLoadCommand::getDirectorId() { return id_director; }
