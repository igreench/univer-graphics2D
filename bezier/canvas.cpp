#include "canvas.h"

#include "math.h"

Canvas::Canvas() {
    width = 0;
    height = 0;
}

QImage Canvas::getImage(int width, int height) {
    this->width = width;
    this->height = height;

    QImage backBuffer(width, height, QImage::Format_RGB888);
    backBuffer.fill(qRgb(0, 0, 0));

    drawBeziers(&backBuffer);

    return backBuffer;
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
    beziers.clear();
}

void Canvas::addPoint(QPoint point) {
    points.push_back(point);
    if (points.size() > 3) {
        beziers.push_back(new Bezier(points[0], points[1], points[2], points[3]));
        points.clear();
    }
}

bool Canvas::isPointInArea(QPoint point) {
    if ((point.x() >= 0) && (point.y() >= 0) && (point.x() < width) && (point.y() < height)) {
        return true;
    }
    return false;
}

QVector <Bezier *> Canvas::getBeziers() {
    return beziers;
}

QVector <QPoint> Canvas::getPoints() {
    return points;
}

void Canvas::drawBeziers(QImage *backBuffer) {
    for (int i = 0; i < beziers.size(); i++) {
        drawBezier(backBuffer, *beziers[i]);
    }
}

int Canvas::pointBezier(int n1, int n2, float perc) {
    return n1 + ((n2 - n1) * perc);
}

void Canvas::drawBezier(QImage *backBuffer, Bezier bezier) {
    QPoint point = bezier.getP0();
    for (float i = 0; i <= 1 ; i += 0.05) {
        int x = pointBezier(pointBezier(pointBezier(bezier.getP0().x(),
                                                    bezier.getP1().x(), i),
                                        pointBezier(bezier.getP1().x(),
                                                    bezier.getP2().x(), i), i),
                            pointBezier(pointBezier(bezier.getP1().x(),
                                                    bezier.getP2().x(), i),
                                        pointBezier(bezier.getP2().x(),
                                                    bezier.getP3().x(), i), i), i);
        int y = pointBezier(pointBezier(pointBezier(bezier.getP0().y(),
                                                    bezier.getP1().y(), i),
                                        pointBezier(bezier.getP1().y(),
                                                    bezier.getP2().y(), i), i),
                            pointBezier(pointBezier(bezier.getP1().y(),
                                                    bezier.getP2().y(), i),
                                        pointBezier(bezier.getP2().y(),
                                                    bezier.getP3().y(), i), i), i);

        drawLine(backBuffer, point, QPoint(x, y), Qt::red);
        //drawPixel(backBuffer, QPoint(x, y), Qt::red);
        point = QPoint(x, y);
    }
    drawLine(backBuffer, point, bezier.getP3(), Qt::red);
}
