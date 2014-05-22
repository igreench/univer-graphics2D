#include "canvas.h"

#include "math.h"

Canvas::Canvas() {
    width = 0;
    height = 0;

    rect = QRect(0, 0, 0, 0);
}

QImage Canvas::getImage(int width, int height) {
    this->width = width;
    this->height = height;

    updateRect();

    QImage backBuffer(width, height, QImage::Format_RGB888);
    backBuffer.fill(qRgb(0, 0, 0));

    createTriangles(texture->getWidth(), texture->getHeight(), texture->getTriangles());
    drawTriagnles(&backBuffer);

    return backBuffer;
}

void Canvas::updateRect() {
    rect.setX(0);
    rect.setY(0);
    rect.setWidth(__min(width, texture->getWidth()));
    if (rect.width() == 0) {
        rect.setWidth(width);
    }
    rect.setHeight(__min(height, texture->getHeight()));
    if (rect.height() == 0) {
        rect.setHeight(height);
    }
}

void Canvas::drawPixel(QImage *backBuffer, QPoint point, QColor color) {
    uchar *bits = backBuffer->bits();
    bits[point.y() * backBuffer->bytesPerLine() + point.x() * 3 + 0] = color.red();
    bits[point.y() * backBuffer->bytesPerLine() + point.x() * 3 + 1] = color.green();
    bits[point.y() * backBuffer->bytesPerLine() + point.x() * 3 + 2] = color.blue();
}

void Canvas::drawPixel(QImage *backBuffer, int x, int y, QColor color) {
    uchar *bits = backBuffer->bits();
    bits[y * backBuffer->bytesPerLine() + x * 3 + 0] = color.red();
    bits[y * backBuffer->bytesPerLine() + x * 3 + 1] = color.green();
    bits[y * backBuffer->bytesPerLine() + x * 3 + 2] = color.blue();
}

void Canvas::drawLine(QImage *backBuffer, QPoint point1, QPoint point2, QColor color) {
    if (point1 != point2) {
        int x1 = point1.x();
        int y1 = point1.y();
        int x2 = point2.x();
        int y2 = point2.y();

        int deltaX = abs(x2 - x1);
        int deltaY = abs(y2 - y1);
        int signX = x1 < x2 ? 1 : -1;
        int signY = y1 < y2 ? 1 : -1;

        int error = deltaX - deltaY;

        drawPixel(backBuffer, x2, y2, color);
        while(x1 != x2 || y1 != y2) {
            drawPixel(backBuffer, x1, y1, color);
            const int error2 = error * 2;

            if (error2 > -deltaY) {
                error -= deltaY;
                x1 += signX;
            }
            if (error2 < deltaX) {
                error += deltaX;
                y1 += signY;
            }
        }
    } else {
        drawPixel(backBuffer, point1.x(), point1.y(), color);
    }
}

void Canvas::drawLineByOX(QImage *backBuffer, int x1, int x2, int y, QColor color) {
    int signx = (x2 - x1) / abs(x2 - x1);

    for (int x = x1; x != x2; x += signx) {
        drawPixel(backBuffer, x, y, color);
    }
}

void Canvas::clear() {
    points.clear();
    triangles.clear();
}

void Canvas::addPoint(QPoint point) {
    points.push_back(point);
}

bool Canvas::isPointInArea(QPoint point) {
    if ((point.x() >= 0) && (point.y() >= 0) && (point.x() < width) && (point.y() < height)) {
        return true;
    }
    return false;
}

QVector <QPoint> Canvas::getPoints() {
    return points;
}

void Canvas::setTexture(QImage image) {
    texture = new Texture(image);
    updateRect();
    texture->createTriangles();
    createTriangles(image.width(), image.height(), texture->getTriangles());
}

void Canvas::createTriangles(int width, int height, QVector <Triangle*> /*triangles*/) {
    triangles.push_back(new Triangle(QPoint(0, 0), QPoint(width, 0), QPoint(width, height)));
    triangles.push_back(new Triangle(QPoint(0, 0), QPoint(0, height), QPoint(width, height)));
}

void Canvas::drawTriagnles(QImage *backBuffer) {
    for (int i = 0; i < triangles.size(); i++) {
        drawTriagnle(backBuffer, triangles[i]);
    }
}

void Canvas::drawTriagnle(QImage *backBuffer, Triangle */*triangle*/) {
    for (int x = rect.x(); x < rect.width(); x++) {
        for (int y = rect.y(); y < rect.height(); y++) {
            drawPixel(backBuffer, x, y, texture->getPixel(x, y));
        }
    }
}
