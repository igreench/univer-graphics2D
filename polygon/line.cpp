#include "line.h"

Line::Line(QPoint p1, QPoint p2) {
    this->p1 = p1;
    this->p2 = p2;
}

QPoint Line::getP1() {
    return p1;
}
QPoint Line::getP2() {
    return p2;
}

QPoint Line::crossPoint(int y) {
    int x = p1.x() + (p2.x() - p1.x()) * (p1.y() - y) / (p1.y() - p2.y());
    return QPoint(x, y);
}

int Line::area(const QPoint &a, const QPoint &b, const QPoint &c) {
    return (b.x() - a.x()) * (c.y() - a.y()) - (b.y() - a.y()) * (c.x() - a.x());
}

bool Line::intersect(int a, int b, int c, int d) {
    if (a > b)  {
        std::swap(a, b);
    }
    if (c > d)  {
        std::swap(c, d);
    }
    return std::max(a, c) <= std::min(b, d);
}

bool Line::isIntersected(Line line1, Line line2) {
    return (intersect(line1.getP1().x(), line1.getP2().x(), line2.getP1().x(), line2.getP2().x() ) &&
            intersect(line1.getP1().y(), line1.getP2().y(), line2.getP1().y(), line2.getP2().y() ) &&
            area(line1.getP1(), line1.getP2(), line2.getP1()) *
            area(line1.getP1(), line1.getP2(), line2.getP2()) <= 0 &&
            area(line2.getP1(), line2.getP2(), line1.getP1()) *
            area(line2.getP1(), line2.getP2(), line1.getP2()) <= 0 );
}
