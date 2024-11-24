#pragma once

#include "Scene.h"
#include "Drawer.h"

#include "pthread.h"

// Абстрактный класс - стратегия для алгоритма трассировки лучей
class RayTracing
{
protected:
    std::shared_ptr<Scene> scene;
    std::shared_ptr<Camera> camera;
    std::shared_ptr<Drawer> drawer;
    size_t maxDepth;

public:
    RayTracing(std::shared_ptr<Scene> _scene, std::shared_ptr<Camera> _camera, std::shared_ptr<Drawer> _drawer, size_t _maxDepth);
    virtual ~RayTracing() = default;

    virtual void render(size_t countThreads = 32) = 0;
    virtual Intensity castRay(Ray &ray, const size_t depth = 0, bool printing = false) const noexcept = 0;

protected:
    double distanceToCamera(Point3 &p) const noexcept;
};
