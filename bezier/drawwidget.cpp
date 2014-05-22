#include "drawwidget.h"

DrawWidget::DrawWidget(QWidget *parent) : QWidget(parent) {
    mx = 0;
    my = 0;
    isDrawBezier = false;
    isMovingPoint = false;
    setMouseTracking(true);
}

void DrawWidget::paintEvent(QPaintEvent */*event*/) {
    QPainter painter(this);
    painter.drawImage(0,0, canvas.getImage(width(), height()));

    painter.setPen(Qt::red);
    painter.setBrush(QBrush(Qt::red));
    for (int i = 0; i < canvas.getPoints().size(); i++) {
        painter.drawEllipse(canvas.getPoints()[i], 2, 2);
    }

    painter.setPen(Qt::green);
    painter.setBrush(QBrush(Qt::green));
    if (isDrawBezier) {
        painter.drawEllipse(mx, my, 4, 4);
    } else {
        for (int i = 0; i < canvas.getBeziers().size(); i++) {
            for (int j = 0; j < canvas.getBeziers()[i]->getPoints().size(); j++) {
                painter.drawEllipse(canvas.getBeziers()[i]->getPoints()[j], 2, 2);
            }
        }
        for (int i = 0; i < activePointsIndexes.size(); i++) {
            painter.drawEllipse(canvas.getBeziers()[activePointsIndexes[i] / 4]->getPoints()[activePointsIndexes[i] % 4] , 4, 4);
        }
    }
}

void DrawWidget::mousePressEvent( QMouseEvent * event) {
    mx = event->x();
    my = event->y();
    if( event->button() == Qt::RightButton ) {
        isDrawBezier = !isDrawBezier;
        if (!isDrawBezier) {
            activePointsIndexes.clear();
        }

    }
    if( event->button() == Qt::LeftButton ){
        if (isDrawBezier) {
            addPoint(QPoint(event->x(), event->y()));
        } else {
            if (!activePointsIndexes.isEmpty()) {
                isMovingPoint = true;
            }
        }
    }
    update();
}

void DrawWidget::mouseMoveEvent( QMouseEvent * event) {
    mx = event->x();
    my = event->y();
    if (!isDrawBezier) {
        if (!isMovingPoint) {
            for (int i = 0; i < canvas.getBeziers().size(); i++) {
                for (int j = 0; j < canvas.getBeziers()[i]->getPoints().size(); j++) {
                    //painter.drawEllipse(canvas.getBeziers()[i]->getPoints()[j], 2, 2);
                    if ((abs(mx - canvas.getBeziers()[i]->getPoints()[j].x()) < 5) &&
                        (abs(my - canvas.getBeziers()[i]->getPoints()[j].y()) < 5)){
                        activePointsIndexes.push_back(i * 4 + j);
                    } else {
                        for (int k = 0; k < activePointsIndexes.size(); k++) {
                            if (activePointsIndexes[k] == i * 4 + j) {
                                activePointsIndexes.remove(k);
                                break;
                            }
                        }
                    }
                }
            }
        } else {
            for (int i = 0; i < activePointsIndexes.size(); i++) {
                canvas.getBeziers()[activePointsIndexes[i] / 4]->setPoint(activePointsIndexes[i] % 4, QPoint(event->x(), event->y()));
            }
        }
    }
    update();
}

void DrawWidget::mouseReleaseEvent( QMouseEvent * /*event*/) {
    if (isMovingPoint) {
        isMovingPoint = false;
    }
}

void DrawWidget::clear() {
    canvas.clear();
    activePointsIndexes.clear();
    update();
}

void DrawWidget::setComment(QString comment) {
    this->comment = comment;
}

QImage DrawWidget::getImage(int width, int height) {
    return canvas.getImage(width, height);
}

void DrawWidget::addPoint(QPoint point) {
    canvas.addPoint(point);
}


