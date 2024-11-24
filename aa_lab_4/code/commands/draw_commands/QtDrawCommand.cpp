#include "QtDrawCommand.h"

QtDrawCommand::QtDrawCommand(QGraphicsView* gv) 
: graphicsView(gv) {}
    
void QtDrawCommand::execute() {
    std::shared_ptr<Drawer> drawer = std::make_shared<QtDrawer>(graphicsView);
    
    std::shared_ptr<Scene> scene = sceneManager->getScene();
    std::shared_ptr<Camera> camera = scene->getActiveCamera();

    drawManager->drawScene(scene, camera, drawer);
}