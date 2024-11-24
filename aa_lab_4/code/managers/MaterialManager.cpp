#include "MaterialManager.h"

MaterialManager::MaterialManager() : materialSolution(MaterialSolution()) {

    materialSolution.registrate(idMaterial::RED, std::make_shared<Material>(Intensity(0.2, 0.2, 0.2),   // ka
                                                                            Intensity(0.6, 0.6, 0.6),   // kd
                                                                            Intensity(0.1, 0.1, 0.1),   // ks
                                                                            50));                   // n
    materialSolution.registrate(idMaterial::BLUE, std::make_shared<Material>(Intensity(0.157, 0.3, 0.34), 
                                                                            Intensity(0.213, 0.5, 0.56), 
                                                                            Intensity(0.05, 0.05, 0.05),
                                                                            5));
}

std::shared_ptr<Material> MaterialManager::getMaterial(idMaterial id) {
    return materialSolution.getMaterial(id);
}


