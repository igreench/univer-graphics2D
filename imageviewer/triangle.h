#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <QPoint>
#include <QVector>

class Triangle
{
public:
    Triangle(QPoint p1, QPoint p2, QPoint p3);

    void setP1(QPoint point);
    QPoint getP1();

    void setP2(QPoint point);
    QPoint getP2();

    void setP3(QPoint point);
    QPoint getP3();

    QVector <QPoint> getPoints();

private:
    QPoint p1;
    QPoint p2;
    QPoint p3;
};

#endif // TRIANGLE_H
