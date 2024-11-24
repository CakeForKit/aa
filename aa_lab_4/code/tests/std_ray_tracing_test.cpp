#include "std_ray_tracing_test.h"



Window::Window(QWidget *parent): QMainWindow(parent)
{
    scene=new QGraphicsScene(this);
    graphicsView=new QGraphicsView(this);
    graphicsView->setScene(scene);
    scene->setSceneRect(0, 0, 388, 572);
    setCentralWidget(graphicsView);
}

void Window::closee() {
    this->close();
}
 

class TestRayTracing : public testing::TestWithParam<raytracing_test_data_t> 
{
public:
    int argc = 0;
    QApplication app = QApplication(argc, NULL);
    std::shared_ptr<Camera> camera;
    std::shared_ptr<RayTracing> rayTracing;
protected:
    void SetUp() override {
        std::shared_ptr<DrawManager> drawManager = std::make_shared<DrawManager>();
        std::shared_ptr<SceneManager> sceneManager = std::make_shared<SceneManager>();
        std::shared_ptr<LoadManager> loadManager = std::make_shared<LoadManager>();
        std::shared_ptr<MaterialManager> materialManager = std::make_shared<MaterialManager>();
        std::shared_ptr<TransformManager> transformManager = std::make_shared<TransformManager>();
        idReaderCreator id_reader = idReaderCreator::TRIANGLES;
        idDirectorCreator id_director = idDirectorCreator::TRIANGLES;
        size_t stepOfRevolving = 10;
        {
            char filename[] = "/home/kathrine/cg_cp/tests/data_for_tests/test_model_4.txt";
            std::shared_ptr<Material> material = materialManager->getMaterial(idMaterial::BLUE);
            PtrObjectScene model = loadManager->loadModelFromFile(id_reader, id_director, filename, stepOfRevolving, material);
            sceneManager->addModel(model);
        }
        {
            char filename[] = "/home/kathrine/cg_cp/tests/data_for_tests/pawn.txt";
            std::shared_ptr<Material> material = materialManager->getMaterial(idMaterial::RED);
            PtrObjectScene model = loadManager->loadModelFromFile(id_reader, id_director, filename, stepOfRevolving, material);
            sceneManager->addModel(model);
        }
        
        Window window;
        window.show();
        window.hide();
        std::shared_ptr<Drawer> drawer = std::make_shared<QtDrawer>(window.graphicsView);
        std::shared_ptr<Scene> scene = sceneManager->getScene();
        camera = scene->getActiveCamera();
        
        size_t pixelsWidth = static_cast<size_t>(drawer->getImgWidth());
        size_t pixelsHeight = static_cast<size_t>(drawer->getImgHeight());
        camera->setCountPixelsViewport(pixelsWidth, pixelsHeight);
        rayTracing = std::make_shared<StandardRayTracing>(scene, camera, drawer);

        // std::cout << "WxH = " << pixelsWidth << "x" << pixelsHeight << std::endl;        
    }

    void TearDown() override {
        app.exit();
    }
};

TEST_P(TestRayTracing, DiffRays) {
    raytracing_test_data_t tdata = GetParam();
    Ray ray = camera->createRay(tdata.xi, tdata.yi);
    Intensity intens = rayTracing->castRay(ray);
    // std::cout << intens << "\n\n";
    EXPECT_TRUE(intens == tdata.expIntens);
}



INSTANTIATE_TEST_SUITE_P(
    RayTracingTestSuite,
    TestRayTracing,
    testing::Values(raytracing_test_data[0], 
                    raytracing_test_data[1], 
                    raytracing_test_data[2], 
                    raytracing_test_data[3])
);
