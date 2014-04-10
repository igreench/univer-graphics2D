#include "drawwidget.h"

DrawWidget::DrawWidget(QWidget *parent) :
    QWidget(parent)
{
    polygon.addPoint(QPoint(100, 100));
    polygon.addPoint(QPoint(200, 200));
    polygon.addPoint(QPoint(150, 250));

    /*polygon.addPoint(QPoint(100, 100));
    polygon.addPoint(QPoint(200, 100));
    polygon.addPoint(QPoint(200, 200));
    polygon.addPoint(QPoint(100, 200));*/

    /*polygon.addPoint(QPoint(100, 100));
    polygon.addPoint(QPoint(120, 120));
    polygon.addPoint(QPoint(140, 100));
    polygon.addPoint(QPoint(160, 120));
    polygon.addPoint(QPoint(180, 100));
    polygon.addPoint(QPoint(180, 200));
    polygon.addPoint(QPoint(100, 200));*/
}

void DrawWidget::paintEvent(QPaintEvent */*event*/) {
    QPainter painter(this);
    painter.drawImage(0,0, polygon.getImage(width(), height()));
    //painter.drawLine();
}

void DrawWidget::addPoint(QPoint point) {
    polygon.addPoint(point);
}

void DrawWidget::clear() {
    polygon.clear();
}

void DrawWidget::setComment(QString comment) {
    this->comment = comment;
}

QVector <QPoint> DrawWidget::getPoints() {
    return polygon.getPoints();
}
