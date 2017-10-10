#ifndef BREAKOUT_H
#define BREAKOUT_H

#pragma once

#include <QWidget>
#include <QKeyEvent>
#include <QMouseEvent>
#include "ball.h"
#include "brick.h"
#include "paddle.h"


class Breakout : public QWidget {

  public:
    Breakout(QWidget *parent = 0);
    ~Breakout();

  protected:
    void paintEvent(QPaintEvent *);
    void timerEvent(QTimerEvent *);
    void keyPressEvent(QKeyEvent *);
    void mousePressEvent(QMouseEvent *);
    void keyReleaseEvent(QKeyEvent *);
    void drawObjects(QPainter *);
    void finishGame(QPainter *, QString);
    void moveObjects();
    void startGame();
    void pauseGame();
    void stopGame();
    void victory();
    void checkCollision();
    void reiniciarBolas();

  private:
    int x;
    int timerId;
    static const int N_OF_BRICKS = 30;
    static const int DELAY = 10;
    static const int BOTTOM_EDGE = 400;
    Ball *ball;
    Paddle *paddle;
    Brick *bricks[N_OF_BRICKS];
    bool gameOver;
    bool gameWon;
    bool perdeuVida;
    bool gameStarted;
    bool paused;
    int numeroTijolos;
    int numeroBolas;
};

#endif // BREAKOUT_H
