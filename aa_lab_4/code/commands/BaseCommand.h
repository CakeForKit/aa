#pragma once

#include "DrawManager.h"
#include "SceneManager.h"
#include "LoadManager.h"
#include "MaterialManager.h"
#include "TransformManager.h"

class BaseCommand 
{
protected:
    std::shared_ptr<DrawManager> drawManager;
    std::shared_ptr<SceneManager> sceneManager;
    std::shared_ptr<LoadManager> loadManager;
    std::shared_ptr<MaterialManager> materialManager;
    std::shared_ptr<TransformManager> transformManager;

public:
    virtual ~BaseCommand() = default;

    void setManagers(std::shared_ptr<DrawManager> _drawManager, 
                    std::shared_ptr<SceneManager> _sceneManager, 
                    std::shared_ptr<LoadManager> _loadManager,
                    std::shared_ptr<MaterialManager> _materialManager,
                    std::shared_ptr<TransformManager> _transformManager) noexcept;
    virtual void execute() = 0;
};
