#include "RayTracing.h"

RayTracing::RayTracing(std::shared_ptr<Scene> _scene, std::shared_ptr<Camera> _camera, std::shared_ptr<Drawer> _drawer,  size_t _maxDepth)
: scene(_scene), camera(_camera), drawer(_drawer), maxDepth(_maxDepth) {}

double RayTracing::distanceToCamera(Point3 &p) const noexcept {
    Point3 cp = camera->getCameraPos();

    return sqrt((p.x() - cp.x()) * (p.x() - cp.x()) + 
            (p.y() - cp.y()) * (p.y() - cp.y()) + (p.z() - cp.z()) * (p.z() - cp.z()));
}

