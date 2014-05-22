#ifndef LINE_H
#define LINE_H

#include <QPoint>

class Line {
public:
    Line(QPoint p1, QPoint p2);
    QPoint getP1();
    QPoint getP2();
    QPoint crossPoint(int y);

    static bool isIntersected(Line line1, Line line2);
    static bool intersect(int a, int b, int c, int d);
    static int area(const QPoint &a, const QPoint &b, const QPoint &c);

private:
    QPoint p1;
    QPoint p2;
};

#endif // LINE_H
