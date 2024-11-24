#include "Scene.h"

std::ostream& operator<<(std::ostream &os, const Scene &scene) {
    return scene.print(os);
}

std::ostream& Scene::print(std::ostream& os) const noexcept {
    os << "Scene: \n";
    os << "Cameras: ----------\n";
    size_t i = 0;
    for (std::shared_ptr<Camera> elem : cameras) {
        os << i << ") " << *elem;
        ++i;
    }
    os << "-------------------\n";
    os << "Models: ----------\n";
    i = 0;
    for (std::shared_ptr<ObjectScene> elem : models) {
        os << i << ") " << *elem;
        ++i;
    }
    os << "-------------------\n";

    return os;
}

Scene::Scene() 
: models(std::vector<std::shared_ptr<ObjectScene>>()), 
cameras(std::vector<std::shared_ptr<Camera>>()), 
lights(std::vector<std::shared_ptr<Light>>()) {
    std::shared_ptr<Camera> c = std::make_shared<Camera>();
    cameras.push_back(c);
    activeCamera = cameras[0];

    lights.push_back(std::make_shared<PointLight>());
    lights.push_back(std::make_shared<AmbientLight>());
}

void Scene::addModel(std::shared_ptr<ObjectScene> model) noexcept {
    models.push_back(model);
}

void Scene::removeModel(size_t ind) {
    size_t count_models = models.size();
    if (count_models == 0) {
        time_t curTime = time(NULL);
        throw NoModelsSceneException(ctime(&curTime), __FILE__, __LINE__, typeid(*this).name(), __func__);
    }
    if (ind >= count_models) {
        time_t curTime = time(NULL);
        throw IndexException(ctime(&curTime), __FILE__, __LINE__, typeid(*this).name(), __func__);
    }
    models.erase(models.begin() + static_cast<long int>(ind));
}

std::shared_ptr<ObjectScene> Scene::getModel(size_t ind) {
    size_t count_models = models.size();
    if (count_models == 0) {
        time_t curTime = time(NULL);
        throw NoModelsSceneException(ctime(&curTime), __FILE__, __LINE__, typeid(*this).name(), __func__);
    }
    if (ind >= count_models) {
        time_t curTime = time(NULL);
        throw IndexException(ctime(&curTime), __FILE__, __LINE__, typeid(*this).name(), __func__);
    }
    return models[ind];
}

void Scene::addCamera() noexcept {
    cameras.push_back(std::make_shared<Camera>());
}

void Scene::removeCamera(size_t ind) {
    size_t count_camera = cameras.size();
    if (count_camera == 1) {
        time_t curTime = time(NULL);
        throw LastCameraSceneException(ctime(&curTime), __FILE__, __LINE__, typeid(*this).name(), __func__);
    }
    if (ind >= count_camera) {
        time_t curTime = time(NULL);
        throw IndexException(ctime(&curTime), __FILE__, __LINE__, typeid(*this).name(), __func__);
    }
    cameras.erase(cameras.begin() + static_cast<long int>(ind));
}

std::shared_ptr<Camera> Scene::getCamera(size_t ind) {
    if (ind >= cameras.size()) {
        time_t curTime = time(NULL);
        throw IndexException(ctime(&curTime), __FILE__, __LINE__, typeid(*this).name(), __func__);
    }
    return cameras[ind];
}

void Scene::setActiveCamera(size_t ind) {
    activeCamera = getCamera(ind);
}

std::shared_ptr<Camera> Scene::getActiveCamera() noexcept {
    return activeCamera;
}

Scene::iteratorLight Scene::beginLight() const noexcept {
    return lights.begin();
}

Scene::iteratorLight Scene::endLight() const noexcept {
    return lights.end();
}

// std::shared_ptr<Light> Scene::getLight() noexcept {
//     return light;
// }

bool Scene::intersection(const Ray &ray, intersection_t &intersect) const {
    intersection_t closest_intersect, now_intersect;
    closest_intersect.distance = std::numeric_limits<double>::max();

    for (std::shared_ptr<ObjectScene> model : models) {
        if (model->intersection(ray, now_intersect) && now_intersect.distance < closest_intersect.distance) {
            closest_intersect = now_intersect;
        }
    }

    // std::cout << "Scene::intersection:\n";
    // std::cout << "Ray: " << ray << std::endl;

    if (fabs(std::numeric_limits<double>::max() - closest_intersect.distance) < EPS)
        return false;

    intersect = closest_intersect;

    // std::cout << "\t" << intersect << std::endl;
    
    return true;
}

size_t Scene::getCountAllFaces() const noexcept {
    size_t count = 0;
    for (std::shared_ptr<ObjectScene> m: models) {
        count += m->getCountFaces();
    }
    return count;
}