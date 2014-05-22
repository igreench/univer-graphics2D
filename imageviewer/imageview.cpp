#include "imageview.h"

ImageView::ImageView(QWidget *parent) : QWidget(parent) {
    mx = 0;
    my = 0;
    //setMouseTracking(true);
    QImage img;
    //img.load("D:/1.jpg");
    img.load("D:/win128.png");
    canvas = new Canvas();
    canvas->setTexture(img);
}

void ImageView::paintEvent(QPaintEvent * /*event*/) {
    QPainter painter(this);
    painter.drawImage(0,0, canvas->getImage(width(), height()));
}

void ImageView::mousePressEvent( QMouseEvent * event) {
    mx = event->x();
    my = event->y();
    update();
}

void ImageView::mouseMoveEvent( QMouseEvent * event) {
    mx = event->x();
    my = event->y();
    update();
}

void ImageView::mouseReleaseEvent( QMouseEvent * /*event*/) {

}
