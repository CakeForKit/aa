#pragma once

#include "DirectorCreator.h"
#include <map>

enum class idDirectorCreator {
    TRIANGLES
};

class DirectorSolution
{
    using mapCreators = std::map<idDirectorCreator, std::shared_ptr<BaseDirectorCreator>>;

private:
    mapCreators map;

public:
    bool registrate(idDirectorCreator id, std::shared_ptr<BaseDirectorCreator> creator);
    bool checkId(idDirectorCreator id) const noexcept;

    std::shared_ptr<BaseDirectorCreator> create(idDirectorCreator id);
};
