#pragma once

#include "VolumeModelImpl.h"
#include "Exceptions.h"


using container_triangles = std::vector<psTriangle>;

class TrianglesModel : public VolumeModelImpl
{
protected:
    container_vertices vertices;    // множество уникальных вершин
    container_triangles triangles;   // множество уникальных стреугольников
    Point3 center;

public:
    TrianglesModel();

    virtual void addFace(std::vector<psPoint3> &lst) override;
    virtual void addFace(std::initializer_list<psPoint3> &lst) override;
    virtual void addFace(std::initializer_list<psPoint3> &&lst) override;
    virtual void setCenter(Point3 &c) noexcept override;
    virtual void setCenter(Point3 &&c) noexcept override;

    virtual container_vertices getVertices() const noexcept override;
    container_triangles getTriangles() const noexcept;
    virtual Point3 getCenter() const noexcept override;

    virtual bool intersection(const Ray &ray, intersection_t &intersect) const override;
    virtual void transform(const std::shared_ptr<TransformAction> action) override;

    virtual size_t getCountFaces() const noexcept override;
    virtual std::ostream& print(std::ostream &os) const noexcept override;

protected:
    virtual std::pair<container_vertices::iterator, bool> addVertex(psPoint3 pv) noexcept override;
};

std::ostream& operator<<(std::ostream &os, const TrianglesModel &model);
