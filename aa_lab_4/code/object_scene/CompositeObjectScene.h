#pragma once

#include "ObjectScene.h"

class CompositeObjectScene: public ObjectScene
{
private:
    VectorPtrObjectScene vec;
public:
    CompositeObjectScene() = default;
    CompositeObjectScene(PtrObjectScene first, ...);

    bool isComposite() const override;
    bool add(std::initializer_list<PtrObjectScene> list) override;
    bool remove(const iterator& it) override;
    iterator begin() const override;
    iterator end() const override;
};