#include "polygon.h"

#include "math.h"

#include <QtCore>

Polygon::Polygon()
{
    width = 0;
    height = 0;
    maxy = 0;
    miny = height;
}

void Polygon::addPoint(QPoint point) {
    points.push_back(point);
}

bool Polygon::createLines() {
    lines.clear();
    if (points.size() > 2) {

        maxy = 0;
        miny = height;

        for (int i = 0; i < points.size() - 1; i++) {
            if (points[i].y() < points[i+1].y()) {
                lines.push_back(new Line(points[i], points[i + 1]));
            } else {
                lines.push_back(new Line(points[i+1], points[i]));
            }
            miny = __min(points[i].y(), miny);
            maxy = __max(points[i].y(), maxy);
        }
        int i1 = points.size() - 1;
        int i2 = 0;

        if (points[i1].y() < points[i2].y()) {
            lines.push_back(new Line(points[i1], points[i2]));
        } else {
            lines.push_back(new Line(points[i2], points[i1]));
        }
        miny = __min(points[points.size() - 1].y(), miny);
        maxy = __max(points[points.size() - 1].y(), maxy);

        return true;
    }
    return false;
}

QImage Polygon::getImage(int width, int height) {
    this->width = width;
    this->height = height;

    lines.clear();
    realPoints.clear();

    QImage backBuffer(width, height, QImage::Format_RGB888);
    backBuffer.fill(qRgb(0, 0, 0));

    if (createLines()) {

        QVector <Line*> activeLines;

        for (int y = miny; y < maxy; y++) {
            QVector <QPoint> crossPoints;

            for (int i = activeLines.size() - 1; i >= 0 ; i--) {
                if (y >= activeLines[i]->getP2().y()) {
                    activeLines.remove(i);
                }
            }

            for (int i = 0; i < lines.size(); i++) {
                if (y == lines[i]->getP1().y()) {
                    activeLines.push_back(lines[i]);
                }
            }

            for (int i = activeLines.size() - 1; i >= 0 ; i--) {
                if (y >= activeLines[i]->getP2().y()) {
                    activeLines.remove(i);
                }
                crossPoints.push_back(activeLines[i]->crossPoint(y));
            }

            qSort(crossPoints.begin(), crossPoints.end(), xLessThan);

            for (int i = 0; i < crossPoints.size() - 1; i++) {
                if ((0 == i % 2) && (crossPoints[i].x() != crossPoints[i + 1].x())) {
                    drawLineByOX(&backBuffer, crossPoints[i].x(),
                                 crossPoints[i + 1].x(),
                                 crossPoints[i].y(),
                                 Qt::red);
                }
            }
        }
    }
    return backBuffer;
}

void Polygon::drawPixel(QImage *backBuffer, QPoint point, QColor color) {
    uchar *bits = backBuffer->bits();
    bits[point.y() * backBuffer->bytesPerLine() + point.x() * 3 + 0] = color.red();
    bits[point.y() * backBuffer->bytesPerLine() + point.x() * 3 + 1] = color.green();
    bits[point.y() * backBuffer->bytesPerLine() + point.x() * 3 + 2] = color.blue();
}

void Polygon::drawPixel(QImage *backBuffer, int x, int y, QColor color) {
    uchar *bits = backBuffer->bits();
    bits[y * backBuffer->bytesPerLine() + x * 3 + 0] = color.red();
    bits[y * backBuffer->bytesPerLine() + x * 3 + 1] = color.green();
    bits[y * backBuffer->bytesPerLine() + x * 3 + 2] = color.blue();
}

void Polygon::drawLine(QImage *backBuffer, QPoint point1, QPoint point2, QColor color) {
    int signx = (point2.x() - point1.x()) / abs(point2.x() - point1.x());
    int signy = (point2.y() - point1.y()) / abs(point2.y() - point1.y());
    int k = signy * abs( (point2.y() - point1.y()) / (point2.x() - point1.x()) );
    for (int x = point1.x(); x != point2.x(); x += signx) {
        int y = point1.y() + ( abs(x - point1.x()) ) * k;
        drawPixel(backBuffer, x, y, color);
    }
}

void Polygon::drawLineByOX(QImage *backBuffer, int x1, int x2, int y, QColor color) {
    int signx = (x2 - x1) / abs(x2 - x1);

    for (int x = x1; x != x2; x += signx) {
        drawPixel(backBuffer, x, y, color);
    }
}

void Polygon::clear() {
    points.clear();
}

bool Polygon::isPointInArea(QPoint point) {
    if ((point.x() >= 0) && (point.y() >= 0) && (point.x() < width) && (point.y() < height)) {
        return true;
    }
    return false;
}

QVector <QPoint> Polygon::getPoints() {
    return points;
}

QVector <Line *> Polygon::getLines() {
    return lines;
}
