#pragma once

#include "VolumeModelReader.h"
#include "TrianglesModelReader.h"
#include "concepts.h"

class BaseReaderCreator {
public:
    virtual ~BaseReaderCreator() = 0;
};

template <typename TBaseReader, typename TReader, typename... Args>
requires NotAbstract<TReader> && Derivative<TReader, TBaseReader> && Constructible<TReader, Args...>
class ReaderCreator : public BaseReaderCreator 
{
public:
    std::shared_ptr<TReader> createReader(Args&... args) const {
        return std::make_shared<TReader>(args...);
    }
};

using TrianglesModelReaderCreator_t = ReaderCreator<Reader, TrianglesModelReader, const char *, size_t>;