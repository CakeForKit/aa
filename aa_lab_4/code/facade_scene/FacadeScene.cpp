#include "FacadeScene.h"


FacadeScene::FacadeScene() {
    drawManager = std::make_shared<DrawManager>();
    sceneManager = std::make_shared<SceneManager>();
    loadManager = std::make_shared<LoadManager>();
    materialManager = std::make_shared<MaterialManager>();
    transformManager = std::make_shared<TransformManager>();

}

void FacadeScene::execute(BaseCommand &cmd) {
    cmd.setManagers(drawManager, sceneManager, loadManager, materialManager, transformManager);
    cmd.execute();
}

size_t FacadeScene::getCountFacesOnScene() {
    return sceneManager->getCountAllFaces();
}