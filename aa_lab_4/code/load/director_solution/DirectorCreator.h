#pragma once

#include "VolumeModelDirector.h"
#include "concepts.h"

#include "TrianglesModelDirector.h"

class BaseDirectorCreator {
public:
    virtual ~BaseDirectorCreator() = 0;
};


template <typename TBaseDirector, typename TDirector, typename... Args>
requires NotAbstract<TDirector> && Derivative<TDirector, TBaseDirector> && Constructible<TDirector, Args...>
class DirectorCreator : public BaseDirectorCreator
{
public:
    std::shared_ptr<TDirector> createDirector(Args&... args) const {
        return std::make_shared<TDirector>(args...);
    } 
};

using TrianglesModelDirectorCreator_t = DirectorCreator<Director, 
                                                        TrianglesModelDirector, 
                                                        std::shared_ptr<VolumeModelReader>, 
                                                        std::shared_ptr<Material>>;