#pragma once

#include "Scene.h"

class SceneManager
{
protected:
    std::shared_ptr<Scene> scene;

public:
    SceneManager();

    std::shared_ptr<Scene> getScene() noexcept;
    size_t getCountAllFaces() const noexcept;

    void addModel(std::shared_ptr<ObjectScene> model) noexcept;
    void removeModel(size_t ind);
    std::shared_ptr<ObjectScene> getModel(size_t ind);

    void addCamera() noexcept;
    void removeCamera(size_t ind);
    std::shared_ptr<Camera> getActiveCamera();
};
