#include "QtDrawer.h"


QtDrawer::QtDrawer(QGraphicsView* canv)
: canvas(canv) {
    int img_width = canvas->viewport()->width();
    int img_height = canvas->viewport()->height();
    img = QImage(img_width, img_height, QImage::Format_RGB32);

    scene = new QGraphicsScene();
}

int QtDrawer::getImgWidth() { return canvas->viewport()->width(); }

int QtDrawer::getImgHeight() { return canvas->viewport()->height(); }

void QtDrawer::setPixelColor(int x, int y, const Color &color) {
    img.setPixelColor(x, y, color.getQColor());
}

void QtDrawer::setPixelColor(int x, int y, const Color &&color) {
    img.setPixelColor(x, y, color.getQColor());
}

void QtDrawer::setScene() {
    // QGraphicsScene* scene = new QGraphicsScene();
    scene->addPixmap(QPixmap::fromImage(img));
    canvas->setScene(scene);
}
