#include "texture.h"

Texture::Texture(QImage image) {
    this->image = image;\
}

void Texture::setImage(QImage image) {
    this->image = image;
}

QImage Texture::getImage() {
    return image;
}

QVector<Triangle*> Texture::getTriangles() {
    return triangles;
}

void Texture::createTriangles() {
    triangles.push_back(new Triangle(QPoint(0, 0), QPoint(image.width(), 0), QPoint(image.width(), image.height())));
    triangles.push_back(new Triangle(QPoint(0, 0), QPoint(0, image.height()), QPoint(image.width(), image.height())));
}

QColor Texture::getPixel(int x, int y) {
    return image.pixel(x, y);
}

QColor Texture::getPixel(QPoint point) {
    return image.pixel(point.x(), point.y());
}

int Texture::getWidth() {
    return image.width();
}

int Texture::getHeight() {
    return image.height();
}
