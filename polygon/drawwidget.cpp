#include "drawwidget.h"

#include "math.h"

DrawWidget::DrawWidget(QWidget *parent) : QWidget(parent) {
    mx = -10;
    my = -10;
    isTracking = false;
    isDrawn = false;
    setMouseTracking(false);
}

void DrawWidget::fill() {
    isDrawn = true;
}

void DrawWidget::paintEvent(QPaintEvent */*event*/) {
    QPainter painter(this);
    painter.fillRect(QRect(0, 0, width(), height()), Qt::black);

    painter.setPen(Qt::green);
    painter.setBrush(QBrush(Qt::green));

    if (isDrawn) {
        painter.drawImage(0,0, polygon.getImage(width(), height()));
        if (getPoints().size() > 2) {
            painter.drawLine(getPoints()[getPoints().size() - 1], getPoints()[0]);
        }
    }

    for (int i = 0; i < getPoints().size() - 1; i++) {
        painter.drawEllipse(getPoints()[i], 2, 2);
        painter.drawLine(getPoints()[i], getPoints()[i + 1]);
    }

    if (getPoints().size() > 2) {
        painter.drawEllipse(getPoints()[getPoints().size() - 1], 2, 2);
    }

    if (isTracking) {
        if (!getPoints().isEmpty()) {
            painter.drawEllipse(getPoints()[0], 8, 8);
        }
        painter.drawEllipse(mx, my, 4, 4);
        if (getPoints().size() > 0) {
            painter.drawLine(getPoints()[getPoints().size() - 1], QPoint(mx, my));
        }
    }
}

void DrawWidget::addPoint(QPoint point) {
    bool isAdd = true;
    if (polygon.createLines()) {
        for (int i = 0; i < polygon.getLines().size(); i++) {
            if ((polygon.getPoints()[polygon.getPoints().size() - 1] != polygon.getLines()[i]->getP1()) &&
                (polygon.getPoints()[polygon.getPoints().size() - 1] != polygon.getLines()[i]->getP2())) {
                if (Line::isIntersected(*polygon.getLines()[i],
                                        Line(point, polygon.getPoints()[polygon.getPoints().size() - 1]))) {
                    isAdd = false;
                    break;
                }
            }
        }
    }
    if (isAdd) {
        polygon.addPoint(point);
        update();
    }
}

void DrawWidget::clear() {
    polygon.clear();
    isDrawn = false;
    update();
}

void DrawWidget::setComment(QString comment) {
    this->comment = comment;
}

QVector <QPoint> DrawWidget::getPoints() {
    return polygon.getPoints();
}

QImage DrawWidget::getImage(int width, int height) {
    return polygon.getImage(width, height);
}

void DrawWidget::mousePressEvent( QMouseEvent * event) {
    if (!isDrawn) {
        mx = event->x();
        my = event->y();
        if (event->button() == Qt::RightButton) {
            isTracking = !isTracking;
            setMouseTracking(isTracking);
        }
        if(event->button() == Qt::LeftButton) {
            if (!getPoints().isEmpty()) {
                if (abs(mx - getPoints()[0].x()) < 5 &&
                    abs(my - getPoints()[0].y()) < 5) {
                    isDrawn = true;
                    isTracking = false;
                }
            }
            if (!isDrawn && isTracking) {
                addPoint(QPoint(event->x(), event->y()));
            }
        }
        update();
    }
}

void DrawWidget::mouseMoveEvent( QMouseEvent * event) {
    if (!isDrawn) {
        if (isTracking) {
            mx = event->x();
            my = event->y();
            update();
        }
    }
}
