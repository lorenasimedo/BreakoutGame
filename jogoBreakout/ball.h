#ifndef BALL_H
#define BALL_H

#pragma once

#include <QImage>
#include <QRect>

class Ball {

  public:
    Ball();
    ~Ball();

  public:
    void resetState();
    void autoMove();
    void setXDir(int);
    void setYDir(int);
    int getXDir();
    int getYDir();
    int eixoX();
    int eixoY();
    QRect getRect();
    QImage & getImage();

  private:
    int xdir;
    int ydir;
    int posicaoX;
    int posicaoY;
    QImage image;
    QRect rect;
    static const int INITIAL_X = 150;
    static const int INITIAL_Y = 320;
    static const int LEFT_EDGE = 10;
    static const int TOP_EDGE = 10;
    static const int RIGHT_EDGE = 300;
};

#endif // BALL_H
