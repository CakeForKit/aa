#include "VolumeModelDirector.h"

VolumeModelDirector::VolumeModelDirector(std::shared_ptr<VolumeModelReader> reader) { (void) reader; }

VolumeModelDirector::~VolumeModelDirector() = default;

std::shared_ptr<ObjectScene> VolumeModelDirector::get() {
    if (!builder->isBuilt()) {
        create();
    }
    return builder->getModel();
}


void VolumeModelDirector::create() {
    builder->readData();
    builder->buildFaces();
    builder->buildCenter();
}