#pragma once

#include "BaseCommand.h"

class FacadeScene
{
private:
    std::shared_ptr<DrawManager> drawManager;
    std::shared_ptr<SceneManager> sceneManager;
    std::shared_ptr<LoadManager> loadManager;
    std::shared_ptr<MaterialManager> materialManager;
    std::shared_ptr<TransformManager> transformManager;

public:
    
    FacadeScene();

    void execute(BaseCommand &cmd);

    size_t getCountFacesOnScene();    
};
