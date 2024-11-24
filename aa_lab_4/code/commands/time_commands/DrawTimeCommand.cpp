#include "DrawTimeCommand.h"

DrawTimeCommand::DrawTimeCommand(QGraphicsView* gv, char *_filename) 
: graphicsView(gv), filename(_filename){}
    
void DrawTimeCommand::execute() {
    std::shared_ptr<Drawer> drawer = std::make_shared<QtDrawer>(graphicsView);
    
    std::shared_ptr<Scene> scene = sceneManager->getScene();
    std::shared_ptr<Camera> camera = scene->getActiveCamera();

    drawManager->collectTimeDataDrawScene(&(filename[0]), scene, camera, drawer);
}