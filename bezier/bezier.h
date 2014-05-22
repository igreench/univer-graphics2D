#ifndef BEZIER_H
#define BEZIER_H

#include <QPoint>
#include <QVector>

class Bezier
{
public:
    Bezier(QPoint p0, QPoint p1, QPoint p2, QPoint p3);

    QPoint getP0();
    QPoint getP1();
    QPoint getP2();
    QPoint getP3();

    void setP0(QPoint point);
    void setP1(QPoint point);
    void setP2(QPoint point);
    void setP3(QPoint point);

    QVector <QPoint> getPoints();

    QPoint getPoint(int n);
    void setPoint(int n, QPoint point);

private:
    QPoint p0;
    QPoint p1;
    QPoint p2;
    QPoint p3;
};

#endif // BEZIER_H
