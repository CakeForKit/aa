#pragma once

#include "Director.h"
#include "VolumeModelBuilder.h"

class VolumeModelDirector : public Director
{
protected:
    std::shared_ptr<VolumeModelBuilder> builder;

public:
    VolumeModelDirector(std::shared_ptr<VolumeModelReader> reader);
    virtual ~VolumeModelDirector() = 0;

    virtual std::shared_ptr<ObjectScene> get();

protected:
    virtual void create();
};
