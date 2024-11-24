#pragma once

#include <initializer_list>
#include <vector>

#include "Vector3.h"
#include "Triangle.h"
#include "intersection_type.h"
#include "TransformAction.h"

using container_vertices = std::vector<psPoint3>;

class VolumeModelImpl
{
public:
    virtual ~VolumeModelImpl() = 0;
    
    virtual void addFace(std::vector<psPoint3> &lst) = 0;
    virtual void addFace(std::initializer_list<psPoint3> &lst) = 0;
    virtual void addFace(std::initializer_list<psPoint3> &&lst) = 0;
    virtual void setCenter(Point3 &c) noexcept = 0;
    virtual void setCenter(Point3 &&c) noexcept = 0;
    
    virtual container_vertices getVertices() const noexcept = 0;
    virtual Point3 getCenter() const noexcept = 0;

    virtual bool intersection(const Ray &ray, intersection_t &intersect) const = 0;
    virtual void transform(const std::shared_ptr<TransformAction> action) = 0;

    virtual size_t getCountFaces() const noexcept = 0;
    virtual std::ostream& print(std::ostream &os) const noexcept = 0;

protected:
    // Возвращает ссылку на итератор который указывает на добавленный обьект, 
    // если добавленный до этого уже был в списке то вернет false
    virtual std::pair<container_vertices::iterator, bool> addVertex(psPoint3 pv) = 0;
};

