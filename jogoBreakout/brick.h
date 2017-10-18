#ifndef BRICK_H
#define BRICK_H

#pragma once

#include <QImage>
#include <QRect>

class Brick {

  public:
    Brick(int, int);
    ~Brick();

  public:
    bool isDestroyed();
    void setDestroyed(bool);
    void setVidas(int);
    void diminuirVidas();
    int numeroVidas();
    QRect getRect();
    void setRect(QRect);
    QImage & getImage();

  private:
    QImage image;
    QRect rect;
    int vida;
    bool destroyed;
};


#endif // BRICK_H
