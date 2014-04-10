#include "circle.h"

#include <math.h>

Circle::Circle()
{
    posX = 0;
    posY = 0;
    R = 0;
}

QImage Circle::getImage(int width, int height) {
    QImage backBuffer(width, height, QImage::Format_RGB888);
    backBuffer.fill(qRgb(255, 255, 255));
   // QPainter painter;
    //painter.begin(&backBuffer);

    //(a < b) ? a : b;
    // (posX - R > 0) ? posX - R : 0
    // (posY - R > 0) ? posY - R : 0
    // (posX + R < this->width()) ? posX + R : this->width()
    // (posY + R < this->height()) ? posY + R : this->height()
    uchar *bits = backBuffer.bits();
    int dx = posX + width / 2;
    int dy = posY + height / 2;
    for (int i = __max(0,-R + dx); i < __min(width, R + dx); i++) {
        for (int j = __max(0, -R + dy); j < __min(height, R+ dy); j++) {\
            if ( pow(i - dx, 2) + pow(j - dy, 2) < pow(R, 2)) {
                //painter.drawPoint(posX + i + width / 2, posY + j + height / 2);
                int x = i;
                int y = j;

                if ((x > 0) && (y > 0) && (x < width) && (y < height)) {
                    bits[y * backBuffer.bytesPerLine() + x * 3 + 0] = 123;
                    bits[y * backBuffer.bytesPerLine() + x * 3 + 1] = 123;
                    bits[y * backBuffer.bytesPerLine() + x * 3 + 2] = 123;
                } /*else {
                    bits[y * backBuffer.bytesPerLine() + x * 3 + 0] = 0;
                    bits[y * backBuffer.bytesPerLine() + x * 3 + 1] = 0;
                    bits[y * backBuffer.bytesPerLine() + x * 3 + 2] = 0;
                }*/
            }
        }
    }
    //painter.end();

    return backBuffer;
}

void Circle::setPosX(int value) {
    posX = value;
}

void Circle::setPosY(int value) {
    posY = value;
}

void Circle::setR(int value) {
    R = value;
}

void Circle::save(QString filename, int width, int height) {
    QPixmap map(width, height);

    //QPainter painter(&map);
    //painter.drawImage(0,0, circle.getImage(width(), height()));
    //painter.drawPixmap(0,0, getImage(width, height));

    map.save(filename,"PNG");
}
