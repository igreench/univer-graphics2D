#ifndef POLYGON_H
#define POLYGON_H

#include <QPoint>
#include <QVector>
#include <QImage>
#include <QColor>

#include <QDebug>

struct Line {
    Line(QPoint p1, QPoint p2) {
        this->p1 = p1;
        this->p2 = p2;

        this->a = p1.y() - p2.y();
        this->b = p2.x() - p1.x();
        this->c = p1.x() * p2.y() - p2.x() * p1.y();
    }

    Line(double a, double b, double c) {
        this->a = a;
        this->b = b;
        this->c = c;
    }

    void update() {
        this->a = p1.y() - p2.y();
        this->b = p2.x() - p1.x();
        this->c = p1.x() * p2.y() - p2.x() * p1.y();
    }

    bool intersected(Line line, QPoint &point) {
        if (intersect (line, *this, point)) {
            qDebug() << "intersect";
            if ((isPointInLineRect(line, point)) &&
                (isPointInLineRect(*this, point))){
                qDebug() << "isPointInLineRect";
                //line.update();
                //this->update();
                //if (line.a * this->b != line.b * this->a) {
                    qDebug() << "non parallel";
                    return true;
                //}
            }
        }
        return false;
    }

    bool isPointInLineRect(Line line, QPoint point) {
        if ((point.x() <= __max(line.p1.x(), line.p2.x())) &&
            (point.x() >= __min(line.p1.x(), line.p2.x())) &&
            (point.y() <= __max(line.p1.y(), line.p2.y())) &&
            (point.y() >= __min(line.p1.y(), line.p2.y()))) {
            return true;
        }
        return false;
    }

    static const double EPS = 1e-9;

    double det (double a, double b, double c, double d) {
        return a * d - b * c;
    }

    bool intersect (Line m, Line n, QPoint & res) {
        double zn = det (m.a, m.b, n.a, n.b);
        if (abs (zn) < EPS)
            return false;
        res.setX( - det (m.c, m.b, n.c, n.b) / zn);
        res.setY( - det (m.a, m.c, n.a, n.c) / zn);
        return true;
    }

    bool parallel (Line m, Line n) {
        return abs (det (m.a, m.b, n.a, n.b)) < EPS;
    }

    bool equivalent (Line m, Line n) {
        return abs (det (m.a, m.b, n.a, n.b)) < EPS
            && abs (det (m.a, m.c, n.a, n.c)) < EPS
            && abs (det (m.b, m.c, n.b, n.c)) < EPS;
    }

    QPoint p1;
    QPoint p2;

    double a, b, c;
};

class Polygon
{
public:
    Polygon();

    void addPoint(QPoint point);
    void clear();
    QImage getImage(int width, int height);

    QVector <QPoint> getPoints();

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

    bool isPointInArea(QPoint point);

    bool xLessThan(const QPoint &p1, const QPoint &p2);
    bool yLessThan(const QPoint &p1, const QPoint &p2);

};

#endif // POLYGON_H
