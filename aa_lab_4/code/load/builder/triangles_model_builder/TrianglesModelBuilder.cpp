#include "TrianglesModelBuilder.h"

TrianglesModelBuilder::TrianglesModelBuilder(std::shared_ptr<VolumeModelReader> reader, std::shared_ptr<Material> _material)
: VolumeModelBuilder(reader, _material) {
    model = std::make_shared<TrianglesModel>();
}