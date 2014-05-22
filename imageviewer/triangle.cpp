#include "triangle.h"

Triangle::Triangle(QPoint p1, QPoint p2, QPoint p3) {
    this->p1 = p1;
    this->p2 = p2;
    this->p3 = p3;
}

void Triangle::setP1(QPoint point) {
    this->p1 = point;
}

QPoint Triangle::getP1() {
    return p1;
}

void Triangle::setP2(QPoint point) {
    this->p2 = point;
}

QPoint Triangle::getP2() {
    return p1;
}

void Triangle::setP3(QPoint point) {
    this->p3 = point;
}

QPoint Triangle::getP3() {
    return p3;
}

QVector <QPoint> Triangle::getPoints() {
    QVector <QPoint> points;
    points.push_back(p1);
    points.push_back(p2);
    points.push_back(p3);
    return points;
}
