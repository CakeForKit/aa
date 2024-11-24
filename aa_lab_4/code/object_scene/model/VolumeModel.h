#pragma once

#include <memory.h>

#include "BaseModel.h"
#include "VolumeModelImpl.h"
#include "Material.h"

class VolumeModel: public Model
{
protected:
    std::shared_ptr<VolumeModelImpl> impl;
    std::shared_ptr<Material> material;

public:
    explicit VolumeModel(std::shared_ptr<VolumeModelImpl> _impl, std::shared_ptr<Material> _material);

    void setMaterial(std::shared_ptr<Material> _material) noexcept;
    std::shared_ptr<Material> getMaterial() const noexcept;
    
    container_vertices getVertices() const noexcept;
    Point3 getCenter() const noexcept;

    virtual bool intersection(const Ray &ray, intersection_t &intersect) const override;
    virtual void transform(const std::shared_ptr<TransformAction> action) override;
    virtual Point3 getCenter() noexcept override;

    virtual size_t getCountFaces() const noexcept override;
    virtual std::ostream& print(std::ostream &os) const noexcept  override;
};