#ifndef CONSOLEMODE_H
#define CONSOLEMODE_H

#include "polygon.h"

class ConsoleMode
{
public:
    ConsoleMode();

    void setSize(int width, int height);
    void addPoint(QPoint point);
    void clear();
    void setComment(QString comment);

    QImage getImage(int width, int height);

private:
    int PanelWidth;
    int PanelHeight;

    Polygon polygon;
    QString comment;
};

#endif // CONSOLEMODE_H
