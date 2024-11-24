#pragma once

#include <memory>
#include <vector>
#include "intersection_type.h"
#include "Ray.h"
#include "TransformAction.h"

class ObjectScene;

using PtrObjectScene = std::shared_ptr<ObjectScene>;
using VectorPtrObjectScene = std::vector<PtrObjectScene>;

class ObjectScene
{
public:
    using value_type = ObjectScene;
    using size_type = size_t;
    using iterator = VectorPtrObjectScene::const_iterator;
    using const_iterator = VectorPtrObjectScene::const_iterator;

    virtual ~ObjectScene() = default;
    virtual bool isComposite() const;
    virtual bool add(std::initializer_list<PtrObjectScene> comp);
    virtual bool remove(const iterator& it);
    virtual iterator begin() const;
    virtual iterator end() const;

    virtual bool intersection(const Ray &ray, intersection_t &intersect) const = 0;
    virtual void transform(const std::shared_ptr<TransformAction> action) = 0;
    virtual Point3 getCenter() noexcept = 0;

    virtual size_t getCountFaces() const noexcept = 0;
    virtual std::ostream& print(std::ostream &os) const noexcept = 0;
};

std::ostream& operator<<(std::ostream &os, const ObjectScene &model);