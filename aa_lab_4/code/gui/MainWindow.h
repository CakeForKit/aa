#pragma once

#include <QMainWindow>
#include <QPushButton>
#include <QMessageBox>
#include <QMouseEvent>
#include "ui_mainWindow.h"
#include "FacadeScene.h"
#include "QtDrawCommand.h"
#include "TrianglesModelLoadCommand.h"
#include "MoveModelCommand.h"
#include "RotateModelCommand.h"
#include "RotateCameraCommand.h"
#include "MaterialSolution.h"
#include "DrawTimeCommand.h"

class MyQGraphicsView : public QGraphicsView
{
public:
    MyQGraphicsView(QWidget *parent = nullptr) : QGraphicsView(parent) {setMouseTracking(true);}

protected:
    void mousePressEvent(QMouseEvent  *event) override {
        std::cout << "MousePressEvent of MyQGraphicsView: ";

        // int width = viewport()->width();
        // int height = viewport()->height();
        // std::cout << width << "x" << height << "\n";
        QPoint pos = event->pos();
        std::cout << "( " << pos.x() << "," << pos.y() << ")\n";

        QGraphicsView::mousePressEvent(event); // Call base class implementation
    }
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parant = nullptr);

private:
    Ui::MainWindow ui;
    MyQGraphicsView *graphicsView;
    FacadeScene facade;

private slots:
    void onLoadModelBtnClicked();
    void onDrawBtnClicked();
    void onMoveModelBtnClicked();
    void onRotateModelBtnClicked();
    void onRotateOXCameraBtnClicked();
    void onRotateOYCameraBtnClicked();

private:
    size_t getSelectedModelId() const;

    void rotateCamera(Axis axis);

public:
    void measureRenderTime();

};
