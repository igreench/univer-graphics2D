#include "consolemode.h"

ConsoleMode::ConsoleMode()
{
    PanelWidth = 0;
    PanelHeight = 0;
}

void ConsoleMode::setSize(int width, int height) {
    PanelWidth = width;
    PanelHeight = height;
}

void ConsoleMode::addPoint(QPoint point) {
    polygon.addPoint(point);
}

void ConsoleMode::clear() {
    polygon.clear();
}

void ConsoleMode::setComment(QString comment) {
    this->comment = comment;
}
