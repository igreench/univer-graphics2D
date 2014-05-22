#ifndef CANVAS_H
#define CANVAS_H

#include <QPoint>
#include <QVector>
#include <QImage>
#include <QColor>

#include "bezier.h"

#include <QDebug>

class Canvas
{
public:
    Canvas();

    void addPoint(QPoint point);
    void clear();
    QImage getImage(int width, int height);

    QVector <Bezier *> getBeziers();
    QVector <QPoint> getPoints();

private:
    QVector <Bezier *> beziers;
    QVector <QPoint> points;

    void drawPixel(QImage *backBuffer, int x, int y, QColor color);
    void drawPixel(QImage *backBuffer, QPoint point, QColor color);
    void drawLine(QImage *backBuffer, QPoint point1, QPoint point2, QColor color);
    void drawLineByOX(QImage *backBuffer, int x1, int x2, int y, QColor color);
    void drawBezier(QImage *backBuffer, Bezier bezier);
    void drawBeziers(QImage *backBuffer);

    int pointBezier(int n1, int n2, float perc);

    bool isPointInArea(QPoint point);

    int width;
    int height;
};

#endif // CANVAS_H
