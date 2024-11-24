#pragma once

#include <gtest/gtest.h>
#include <QGraphicsView>
#include <QMainWindow>
#include <QApplication>
#include "FacadeScene.h"
#include "QtDrawCommand.h"
#include "TrianglesModelLoadCommand.h"
#include "MoveModelCommand.h"
#include "RotateModelCommand.h"
#include "RotateCameraCommand.h"
#include "MaterialSolution.h"
#include "DrawTimeCommand.h"

struct raytracing_test_data_t {
    int xi;
    int yi;
    Intensity expIntens;
};


const raytracing_test_data_t raytracing_test_data[] = {
    { 190, 443, Intensity(0, 0, 0) },                       // нет пересечений луча
    { 95, 238, Intensity(0.0208158, 0.0415989, 0.0470047) },    // луч пересекается с обьектом один раз
    { 131, 351, Intensity(0.101881, 0.23196, 0.260216) },       // луч пересекается с обьектом и отражается
    { 46, 511, Intensity(0.132294, 0.303488, 0.340289) },       // луч пересекается с обьектом в тени др обьекта
};

class Window : public QMainWindow
{
    Q_OBJECT
public:
    Window(QWidget *parent = 0);
    ~Window() = default;

    void closee();

    QGraphicsScene* scene;
    QGraphicsView* graphicsView;
};