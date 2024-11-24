#include "MaterialSolution.h"

bool MaterialSolution::registrate(idMaterial id, std::shared_ptr<Material> material) {
    return map.insert(mapMaterial::value_type(id, material)).second;
}

bool MaterialSolution::checkId(idMaterial id) {
    return map.find(id) != map.end();
}

std::shared_ptr<Material> MaterialSolution::getMaterial(idMaterial id) {
    mapMaterial::const_iterator it = map.find(id);

    if (it == map.end())
        return nullptr;
    else {
        mapMaterial::value_type elem = *it;
        return std::shared_ptr<Material>(elem.second);
    }
}