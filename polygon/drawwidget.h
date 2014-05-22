#ifndef DRAWWIDGET_H
#define DRAWWIDGET_H

#include <QWidget>
#include <QPainter>
#include <QMouseEvent>
#include "polygon.h"

class DrawWidget : public QWidget
{
    Q_OBJECT
public:
    explicit DrawWidget(QWidget *parent = 0);

    void setComment(QString comment);
    QVector <QPoint> getPoints();
    QImage getImage(int width, int height);
    void fill();

public slots:
    void clear();
    void addPoint(QPoint point);

protected:
    virtual void paintEvent(QPaintEvent *event);
    virtual void mousePressEvent( QMouseEvent * event);
    virtual void mouseMoveEvent( QMouseEvent * event);

private:
    Polygon polygon;
    QString comment;
    int mx, my;
    bool isTracking;
    bool isDrawn;

};

#endif // DRAWWIDGET_H
