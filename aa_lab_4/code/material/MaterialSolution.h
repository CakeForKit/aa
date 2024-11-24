#pragma once

#include "Material.h"

#include <map>
#include <memory>

enum class idMaterial {
    RED,
    BLUE
};

class MaterialSolution
{
    using mapMaterial = std::map<idMaterial, std::shared_ptr<Material>>;

private:
    mapMaterial map;

public:
    bool registrate(idMaterial id, std::shared_ptr<Material> material);
    bool checkId(idMaterial id);

    std::shared_ptr<Material> getMaterial(idMaterial id);
};
