#ifndef POLYGON_H
#define POLYGON_H

#include <QPoint>
#include <QVector>
#include <QImage>
#include <QColor>

#include <QDebug>

#include "line.h"

class Polygon
{
public:
    Polygon();

    void addPoint(QPoint point);
    void clear();
    QImage getImage(int width, int height);

    QVector <QPoint> getPoints();
    QVector <Line *> getLines();

    bool createLines();

private:
    QVector <QPoint> points;
    QVector <QPoint> realPoints;
    QVector <Line *> lines;

    void drawPixel(QImage *backBuffer, int x, int y, QColor color);
    void drawPixel(QImage *backBuffer, QPoint point, QColor color);
    void drawLine(QImage *backBuffer, QPoint point1, QPoint point2, QColor color);
    void drawLineByOX(QImage *backBuffer, int x1, int x2, int y, QColor color);

    int width;
    int height;
    int miny;
    int maxy;

    bool isPointInArea(QPoint point);

    static bool xLessThan(const QPoint &p1, const QPoint &p2) {
            return p1.x() < p2.x();
    }
};

#endif // POLYGON_H
