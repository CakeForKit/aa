#include "TrianglesModelDirector.h"

TrianglesModelDirector::TrianglesModelDirector(std::shared_ptr<VolumeModelReader> reader, std::shared_ptr<Material> material)
: VolumeModelDirector(reader) {
    builder = std::make_shared<TrianglesModelBuilder>(reader, material);
}
