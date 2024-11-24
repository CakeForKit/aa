#include "SceneManager.h"

SceneManager::SceneManager() : scene(std::make_shared<Scene>()) {}

std::shared_ptr<Scene> SceneManager::getScene() noexcept {
    return scene;
}

size_t SceneManager::getCountAllFaces() const noexcept {
    return scene->getCountAllFaces();
}

void SceneManager::addModel(std::shared_ptr<ObjectScene> model) noexcept {
    scene->addModel(model);
}

void SceneManager::removeModel(size_t ind) {
    scene->removeModel(ind);
}

std::shared_ptr<ObjectScene> SceneManager::getModel(size_t ind) {
    return scene->getModel(ind);
}

void SceneManager::addCamera() noexcept {
    scene->addCamera();
}

void SceneManager::removeCamera(size_t ind) {
    scene->removeCamera(ind);
}

std::shared_ptr<Camera> SceneManager::getActiveCamera() {
    return scene->getActiveCamera();
}