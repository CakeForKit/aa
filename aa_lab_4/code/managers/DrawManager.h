#pragma once

#include "StandardRayTracing.h"
#include <sys/time.h>
#include <fstream>

class DrawManager
{
protected:
    // TODO solution, change_alg(), index_in_config
public:

    void drawScene(std::shared_ptr<Scene> scene, std::shared_ptr<Camera> camera, std::shared_ptr<Drawer> drawer);
    void collectTimeDataDrawScene(char *filename, 
                                    std::shared_ptr<Scene> scene, 
                                    std::shared_ptr<Camera> camera, 
                                    std::shared_ptr<Drawer> drawer);
};
