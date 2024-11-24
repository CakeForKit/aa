#include "DirectorSolution.h"

bool DirectorSolution::registrate(idDirectorCreator id, std::shared_ptr<BaseDirectorCreator> creator) {
    return map.insert(mapCreators::value_type(id, creator)).second;
}

bool DirectorSolution::checkId(idDirectorCreator id) const noexcept {
    return map.find(id) != map.end();
}

std::shared_ptr<BaseDirectorCreator> DirectorSolution::create(idDirectorCreator id) {
    mapCreators::const_iterator it = map.find(id);

    if (it == map.end())
        return nullptr;
    else {
        mapCreators::value_type elem = *it;
        return std::shared_ptr<BaseDirectorCreator>(elem.second);
    }
}