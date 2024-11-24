#pragma once

#include "ObjectScene.h"

class Director
{
public:
    virtual ~Director() = 0;

    virtual std::shared_ptr<ObjectScene> get() = 0;

protected:
    virtual void create() = 0;
};
