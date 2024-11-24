#pragma once

#include "VolumeModelBuilder.h"
#include "TrianglesModel.h"

class TrianglesModelBuilder : public VolumeModelBuilder
{
public:
    TrianglesModelBuilder(std::shared_ptr<VolumeModelReader> reader, std::shared_ptr<Material> _material);
};