#ifndef DRAWWIDGET_H
#define DRAWWIDGET_H

#include <QWidget>
#include <QPainter>
#include "polygon.h"

class DrawWidget : public QWidget
{
    Q_OBJECT
public:
    explicit DrawWidget(QWidget *parent = 0);

    void addPoint(QPoint point);
    void clear();
    void setComment(QString comment);

    QVector <QPoint> getPoints();

protected:
    void paintEvent(QPaintEvent *event);

private:
    Polygon polygon;
    QString comment;

};

#endif // DRAWWIDGET_H
