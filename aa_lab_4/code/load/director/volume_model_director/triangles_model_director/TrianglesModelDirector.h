#pragma once

#include "VolumeModelDirector.h"
#include "TrianglesModelBuilder.h"

class TrianglesModelDirector : public VolumeModelDirector
{
public:
    TrianglesModelDirector(std::shared_ptr<VolumeModelReader> reader, std::shared_ptr<Material> material);
};
