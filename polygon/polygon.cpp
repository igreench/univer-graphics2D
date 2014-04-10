#include "polygon.h"

#include "math.h"



Polygon::Polygon()
{
    width = 0;
    height = 0;
}

void Polygon::addPoint(QPoint point) {
    points.push_back(point);
}


QImage Polygon::getImage(int width, int height) {
    this->width = width;
    this->height = height;

    lines.clear();
    realPoints.clear();

    QImage backBuffer(width, height, QImage::Format_RGB888);
    backBuffer.fill(qRgb(0, 0, 0));

    if (points.size() > 2) {

        int maxy = 0;
        int miny = height;

        for (int i = 0; i < points.size() - 1; i++) {
            drawPixel(&backBuffer, points[i], Qt::yellow);
            if (points[i].y() < points[i+1].y())
            {
                lines.push_back(new Line(points[i], points[i + 1]));
            }
            else
            {
                lines.push_back(new Line(points[i+1], points[i]));
            }
            miny = __min(points[i].y(), miny);
            maxy = __max(points[i].y(), maxy);
        }
        int i1 = points.size() - 1;
        int i2 = 0;
        if (points[i1].y() < points[i2].y())
        {
            lines.push_back(new Line(points[i1], points[i2]));
        }
        else
        {
            lines.push_back(new Line(points[i2], points[i1]));
        }
        //lines.push_back(new Line(points[points.size() - 1], points[0]));
        //drawPixel(&backBuffer, points[points.size() - 1], Qt::yellow);
        miny = __min(points[points.size() - 1].y(), miny);
        maxy = __max(points[points.size() - 1].y(), maxy);

        QVector <Line*> filledLines;
        qDebug() << "drawing:";
        QVector <Line*> activeLines;
        for (int y = miny; y < maxy; y++) {
            QVector <QPoint> crossPoints;
            qDebug() << "y: " << y;
            Line line(QPoint(0, y), QPoint(width - 1, y));

            for (int i = 0; i < lines.size(); i++) {
                if (y == lines[i]->p1.y()) {
                    activeLines.push_back(lines[i]);
                }
            }
            QVector<Line*>::iterator iter = activeLines.begin();
            //for (int i = 0; i < activeLines.size(); i++) {
            for (; iter != activeLines.end(); iter++) {
                //
                if (y == (*iter)->p2.y()) {
                    iter = activeLines.erase(iter);
                    if (iter == activeLines.end())
                        break;
                }

                qDebug() << "line:";
                qDebug() << (*iter)->p1;
                qDebug() << (*iter)->p2;
                QPoint point;
                if ((*iter)->intersected(line, point)) {
                    qDebug() << "intersected";
                    bool isGood = true;
                    for (int k = 0; k < crossPoints.size(); k++) {
                        if (crossPoints[k] == point) {
                            isGood = false;
                        }
                    }
                    if (isGood) {
                        crossPoints.push_back(point);
                    }
                }
            }

            qDebug() << "crossPoints:";
            qDebug() << crossPoints;
            for (int i = 0; i < crossPoints.size() - 1; i++) {
                qDebug() << crossPoints[i];
                if (0 == i % 2) {
                    drawLineByOX(&backBuffer, crossPoints[i].x(),
                                 crossPoints[i + 1].x(),
                                 crossPoints[i].y(),
                                 Qt::red);
                }
            }
        }

        for (int i = 0; i < filledLines.size(); i++) {
            drawLineByOX(&backBuffer, filledLines[i]->p1.x(), filledLines[i]->p2.x(), filledLines[i]->p1.y(), Qt::red);
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
