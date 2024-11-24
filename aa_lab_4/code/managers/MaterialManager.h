#pragma once

#include "MaterialSolution.h"

class MaterialManager
{
protected:
    MaterialSolution materialSolution;

public:
    MaterialManager();

    std::shared_ptr<Material> getMaterial(idMaterial id);
};
