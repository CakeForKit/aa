#pragma once

#include "RayTracing.h"

class StandardRayTracing : public RayTracing
{
public:
    StandardRayTracing(std::shared_ptr<Scene> _scene, std::shared_ptr<Camera> _camera, std::shared_ptr<Drawer> _drawer, size_t _maxDepth = 3);

    virtual void render(size_t countThreads);
    virtual Intensity castRay(Ray &ray, const size_t depth = 0, bool printing = false) const noexcept;

protected:
    void renderOneThread();
    void renderParallel(size_t countThreads);
};

struct threadData_t {
    StandardRayTracing *alg;
    Ray ray;
    Intensity intens;
};
