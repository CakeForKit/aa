#pragma once

#include "ReaderCreator.h"
#include <map>

enum class idReaderCreator {
    TRIANGLES
};

class ReaderSolution
{
    // using fCreateReaderCreator = std::shared_ptr<std::shared_ptr<ReaderCreator<TBaseReader, TReader, Args...>>>(&)();
    using mapCreators = std::map<idReaderCreator, std::shared_ptr<BaseReaderCreator>>;

private:
    mapCreators map;

public:
    bool registrate(idReaderCreator id, std::shared_ptr<BaseReaderCreator> creator);
    bool checkId(idReaderCreator id) const noexcept;

    std::shared_ptr<BaseReaderCreator> create(idReaderCreator id);
};
