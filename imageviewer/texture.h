#ifndef TEXTURE_H
#define TEXTURE_H

#include <QImage>
#include <QVector>
#include <QPoint>
#include <QColor>
#include "triangle.h"

class Texture
{
public:
    Texture(QImage image);

    void setImage(QImage image);
    QImage getImage();
    QColor getPixel(int x, int y);
    QColor getPixel(QPoint point);
    int getWidth();
    int getHeight();
    void createTriangles();
    QVector <Triangle*> getTriangles();

private:
    QImage image;
    QVector <Triangle*> triangles; //texture triangles
};

#endif // TEXTURE_H
