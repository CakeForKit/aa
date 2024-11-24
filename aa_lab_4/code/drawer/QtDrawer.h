#pragma once

#include <QGraphicsView>
#include <QImage>
#include <memory>

#include "Drawer.h"

class QtDrawer : public Drawer
{
protected:
    QGraphicsView* canvas;
    QGraphicsScene* scene;
    QImage img;

public:
    QtDrawer(QGraphicsView* canv);

    virtual int getImgWidth() override;
    virtual int getImgHeight() override;

    virtual void setPixelColor(int x, int y, const Color &color) override;
    virtual void setPixelColor(int x, int y, const Color &&color) override;
    virtual void setScene() override;
};
