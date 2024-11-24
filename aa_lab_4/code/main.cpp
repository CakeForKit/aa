#include "MainWindow.h"

#include <iostream>
#include <gtest/gtest.h>

#include "Vector3.h"

void see_work_vector() {
    Vector3 v0;
    Vector3 v1(1, 2, 3);
    Vector3 v2(v1);
    Vector3 v3 = Vector3(1, 1, 1);
    v2 = v0;
    v2.setX(4);
    std::cout << "(0, 0, 0)(1, 2, 3)(4, 0, 0)(1, 1, 1)" << std::endl;
    std::cout << v0 << v1 << v2 << v3 << std::endl;

    std::cout << "4 = " << v1.scalarProduct(v2) << std::endl;
    v3 = Vector3(3, 2, 1, 0.5);
    std::cout << v1 << v3 << std::endl;
    std::cout << "(-8, 16, -8) = " << v1.vectorProduct(v3) << std::endl;

    std::cout << "3.7416 " << v1.length() << std::endl;
    std::cout << v1.normalized() << std::endl;
}

#include "Triangle.h"

void see_work_triangle() {
    std::shared_ptr<Point3> p1, p2, p3, p4;
    p1 = std::make_shared<Point3>();
    p2 = std::make_shared<Point3>(1, 1, 1);
    p3 = std::make_shared<Point3>(1, 2, 3);
    p4 = std::make_shared<Point3>(11, 0, 0);

    Triangle tr1(p1, p2, p3);
    std::cout << "tr1 = ";
    tr1.print_debug_info();
    p1->setX(11);                           // В этот момент может нарушиться целостность обьекта, Надо убрать возможность ихменять координаты точки снаружи
    std::cout << "tr1 = ";
    tr1.print_debug_info();

    Triangle tr2(tr1);
    std::cout << "tr2 = ";
    tr2.print_debug_info();

    Triangle tr3(p2, p4, p3);
    std::cout << "tr3 = ";
    tr3.print_debug_info();
    std::cout << "tr3 == tr1 - " << (tr1 == tr3) << std::endl;
}

#include "TrianglesModel.h"

void see_work_triangles_model() {
    std::cout << "see_work_triangles_model: \n";

    TrianglesModel model;
    {
        std::shared_ptr<Point3> p1, p2, p3, p4, same_p2;
        p1 = std::make_shared<Point3>();
        p2 = std::make_shared<Point3>(1, 1, 1);
        p3 = std::make_shared<Point3>(1, 2, 3);
        p4 = std::make_shared<Point3>(3, 4, 3);
        same_p2 = std::make_shared<Point3>(1, 1, 1);
        std::cout << "use_count p1 = " << p1.use_count() << std::endl;
        
        model.addFace({p1, p2, p3});
        model.addFace({p1, same_p2, p4});
        model.addFace({p2, p4, p1});
    }

    std::cout << model;
    

    for (auto p : model.getVertices()) {
        p->setX(p->x() + 10);
    }
    std::cout << "\ncoord x += 10:" << std::endl;

    std::cout << model;
}

#include "Scene.h"

void see_work_scene() {
    Scene scene;
    std::cout << scene << std::endl;
    scene.addCamera();
    std::cout << *(scene.getCamera(1)) <<std::endl;
    std::cout << scene;
}

#include "TrianglesModelReader.h"

void see_work_read() {
    try {
        TrianglesModelReader reader("/home/kathrine/cg_cp/data/test_model_1.txt");
        reader.open();
        reader.readData();
    } catch (BaseException &ex) {
        std::cout << ex.what() << "\n";
    }
    
}

int main(int argc, char **argv)
{
    std::cout << "It works!" << std::endl;
    // see_work_scene();

    if (argc == 2) {
        std::cout << "See params" << std::endl;

        if (strcmp(argv[1], "-test") == 0) {

            ::testing::InitGoogleTest(&argc, argv);

            return RUN_ALL_TESTS();
        } else if (strcmp(argv[1], "-s") == 0) {
            try {
                // see_work_director();
            } catch (BaseException &ex) {
                std::cout << ex.what() << "\n";
            }
        } else if (strcmp(argv[1], "-time") == 0) {
            QApplication app (argc, argv);
            MainWindow mainwindow;
            mainwindow.show();
            mainwindow.hide();
            mainwindow.measureRenderTime();
            return app.exec();
        }
    } else {
        QApplication app (argc, argv);
        MainWindow mainwindow;
        mainwindow.show();
        return app.exec();
    }

}
