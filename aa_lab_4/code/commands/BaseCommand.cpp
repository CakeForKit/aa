#include "BaseCommand.h"


void BaseCommand::setManagers(std::shared_ptr<DrawManager> _drawManager, 
                                std::shared_ptr<SceneManager> _sceneManager, 
                                std::shared_ptr<LoadManager> _loadManager,
                                std::shared_ptr<MaterialManager> _materialManager,
                                std::shared_ptr<TransformManager> _transformManager) noexcept{
    drawManager = _drawManager;
    sceneManager = _sceneManager;
    loadManager = _loadManager;
    materialManager = _materialManager;
    transformManager = _transformManager;
}