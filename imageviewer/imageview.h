#ifndef IMAGEVIEW_H
#define IMAGEVIEW_H

#include <QWidget>
#include <QPainter>
#include <QMouseEvent>

#include "canvas.h"

class ImageView : public QWidget
{
    Q_OBJECT
public:
    explicit ImageView(QWidget *parent = 0);

protected:
    virtual void paintEvent(QPaintEvent *event);
    virtual void mousePressEvent( QMouseEvent * event);
    virtual void mouseMoveEvent( QMouseEvent * event);
    virtual void mouseReleaseEvent( QMouseEvent * event);

private:
    Canvas *canvas;
    int mx;
    int my;
};

#endif // IMAGEVIEW_H
