#include "VolumeModel.h"

std::ostream& VolumeModel::print(std::ostream &os) const noexcept {
    return impl->print(os);
}

VolumeModel::VolumeModel(std::shared_ptr<VolumeModelImpl> _impl, std::shared_ptr<Material> _material) 
: impl(_impl), material(_material) {}

container_vertices VolumeModel::getVertices() const noexcept {
    return impl->getVertices();
}

Point3 VolumeModel::getCenter() const noexcept {
    return impl->getCenter();
}

bool VolumeModel::intersection(const Ray &ray, intersection_t &intersect) const {
    intersect.material = material;
    return impl->intersection(ray, intersect);
}

void VolumeModel::transform(const std::shared_ptr<TransformAction> action) {
    impl->transform(action);
}

Point3 VolumeModel::getCenter() noexcept {
    return impl->getCenter();
}

void VolumeModel::setMaterial(std::shared_ptr<Material> _material) noexcept {
    material = _material;
}

std::shared_ptr<Material> VolumeModel::getMaterial() const noexcept {
    return material;
}

size_t VolumeModel::getCountFaces() const noexcept {
    return impl->getCountFaces();
}