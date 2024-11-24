#pragma once

#include "ObjectScene.h"
#include "Camera.h"
#include "Light.h"

class Scene
{
public:
    using iteratorLight = std::vector<std::shared_ptr<Light>>::const_iterator;

protected:
    std::vector<std::shared_ptr<ObjectScene>> models;
    std::vector<std::shared_ptr<Camera>> cameras;
    std::shared_ptr<Camera> activeCamera; // указатель на камеру через которую сейчас смотрим. Один из элементов cameras
    std::vector<std::shared_ptr<Light>> lights;

public:
    Scene();

    void addModel(std::shared_ptr<ObjectScene> model) noexcept;
    void removeModel(size_t ind);
    std::shared_ptr<ObjectScene> getModel(size_t ind);

    void addCamera() noexcept;
    void removeCamera(size_t ind);
    std::shared_ptr<Camera> getCamera(size_t ind);
    void setActiveCamera(size_t ind);
    std::shared_ptr<Camera> getActiveCamera() noexcept;

    iteratorLight beginLight() const noexcept;
    iteratorLight endLight() const noexcept;
    // std::shared_ptr<Light> getLight() noexcept;

    bool intersection(const Ray &ray, intersection_t &intersect) const;

    // TODO clearScene()
    size_t getCountAllFaces() const noexcept;
    std::ostream& print(std::ostream& os) const noexcept;
};

std::ostream& operator<<(std::ostream &os, const Scene &scene);


