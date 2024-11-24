#include "ReaderSolution.h"

bool ReaderSolution::registrate(idReaderCreator id, std::shared_ptr<BaseReaderCreator> creator) {
    return map.insert(mapCreators::value_type(id, creator)).second;
}

bool ReaderSolution::checkId(idReaderCreator id) const noexcept {
    return map.find(id) != map.end();
}

std::shared_ptr<BaseReaderCreator> ReaderSolution::create(idReaderCreator id) {
    mapCreators::const_iterator it = map.find(id);

    if (it == map.end())
        return nullptr;
    else {
        mapCreators::value_type elem = *it;
        return std::shared_ptr<BaseReaderCreator>(elem.second);
    }
}

