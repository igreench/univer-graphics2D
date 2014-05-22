#ifndef CANVAS_H
#define CANVAS_H

#include <QPoint>
#include <QVector>
#include <QImage>
#include <QColor>

#include "texture.h"
#include "triangle.h"

#include <QDebug>

class Canvas
{
public:
    Canvas();

    void addPoint(QPoint point);
    void clear();
    QImage getImage(int width, int height);
    void setTexture(QImage image);

    QVector <QPoint> getPoints();

private:
    QVector <QPoint> points;
    Texture *texture;
    QVector <Triangle*> triangles; //real triangles

    void drawPixel(QImage *backBuffer, int x, int y, QColor color);
    void drawPixel(QImage *backBuffer, QPoint point, QColor color);
    void drawLine(QImage *backBuffer, QPoint point1, QPoint point2, QColor color);
    void drawLineByOX(QImage *backBuffer, int x1, int x2, int y, QColor color);
    void drawTriagnles(QImage *backBuffer);
    void drawTriagnle(QImage *backBuffer, Triangle *triangle);

    bool isPointInArea(QPoint point);
    void updateRect();

    void createTriangles(int width, int height, QVector <Triangle*> triangles);

    int width;
    int height;

    QRect rect;
};

#endif // CANVAS_H
