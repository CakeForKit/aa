#pragma once

#include "ObjectScene.h"

class Model: public ObjectScene
{
public:
    virtual ~Model() = 0;

    virtual std::ostream& print(std::ostream &os) const noexcept = 0;

    // accept
    // clone
};