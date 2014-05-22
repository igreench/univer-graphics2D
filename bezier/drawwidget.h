#ifndef DRAWWIDGET_H
#define DRAWWIDGET_H

#include <QWidget>
#include <QPainter>
#include <QMouseEvent>
#include "canvas.h"

class DrawWidget : public QWidget
{
    Q_OBJECT
public:
    explicit DrawWidget(QWidget *parent = 0);

    void setComment(QString comment);
    QImage getImage(int width, int height);

public slots:
    void clear();
    void addPoint(QPoint point);

protected:
    virtual void paintEvent(QPaintEvent *event);
    virtual void mousePressEvent( QMouseEvent * event);
    virtual void mouseMoveEvent( QMouseEvent * event);
    virtual void mouseReleaseEvent( QMouseEvent * event);

private:
    Canvas canvas;
    QString comment;
    int mx, my;
    bool isDrawBezier;
    bool isMovingPoint;
    QVector <int> activePointsIndexes;
};

#endif // DRAWWIDGET_H
