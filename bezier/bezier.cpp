#include "bezier.h"

Bezier::Bezier(QPoint p0, QPoint p1, QPoint p2, QPoint p3) {
    this->p0 = p0;
    this->p1 = p1;
    this->p2 = p2;
    this->p3 = p3;
}

QPoint Bezier::getP0() {
    return p0;
}

QPoint Bezier::getP1() {
    return p1;
}

QPoint Bezier::getP2() {
    return p2;
}

QPoint Bezier::getP3() {
    return p3;
}

void Bezier::setP0(QPoint point) {
    p0 = point;
}

void Bezier::setP1(QPoint point) {
    p1 = point;
}

void Bezier::setP2(QPoint point) {
    p2 = point;
}

void Bezier::setP3(QPoint point) {
    p3 = point;
}

QVector <QPoint> Bezier::getPoints() {
    QVector <QPoint> points;
    points.push_back(p0);
    points.push_back(p1);
    points.push_back(p2);
    points.push_back(p3);
    return points;
}

QPoint Bezier::getPoint(int n) {
    //return getPoints()[n];
    switch (n) {
        break;
    case 1:
        return p1;
        break;
    case 2:
        return p2;
        break;
    case 3:
        return p3;
        break;
    }
    return p0;
}

void Bezier::setPoint(int n, QPoint point) {
    switch (n) {
    case 0:
        p0 = point;
        break;
    case 1:
        p1 = point;
        break;
    case 2:
        p2 = point;
        break;
    case 3:
        p3 = point;
        break;
    }
}
