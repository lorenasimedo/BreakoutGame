#ifndef BREAKOUT_H
#define BREAKOUT_H

#pragma once

#include <QWidget>
#include <QKeyEvent>
#include <QMouseEvent>
#include <QMediaPlayer>
#include <QPushButton>
#include <QObject>
#include "ball.h"
#include "brick.h"
#include "paddle.h"
#include "level.h"
#include "menu.h"



class Breakout : public QWidget {
Q_OBJECT
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
    void printMessage(QPainter *, QString, QString, QString, QString);
    void moveObjects();
    void atualizarAtributos(QPainter *);
    void restartGame();
    void resetGame();
    void pauseGame();
    void stopGame();
    void victory();
    void checkCollision();
    void ligarMusica();
    void reiniciarBolas();
    void continuarMusica();
    void musicaTijoloDestruido();
    void musicaBateuBarra();
    void atualizarLevel();
    void explodirBomba(int);
  public slots:
    void alguemClicou();
  private:
    int x;
    int timerId;
    static const int N_OF_BRICKS = 30;
    int DELAY;
    static const int BOTTOM_EDGE = 400;
    static const int LEFT_EDGE = 10;
    static const int TOP_EDGE = 10;
    static const int RIGHT_EDGE = 300;
    QMediaPlayer *musicaBackground;
    QMediaPlayer *musicaTijolo;
    QMediaPlayer *musicaBarra;
    menu *menucriado;
    Ball *ball;
    Paddle *paddle;
    Level *level;
    Brick *bricks[N_OF_BRICKS];
    bool gameOver;
    bool telaInformativa;
    bool gameWon;
    bool makeDelay;
    bool perdeuVida;
    bool gameStarted;
    bool showInformation;
    bool paused;
    bool TimerActive;
    int numeroTijolos;
    int numeroBolas;
};

#endif // BREAKOUT_H
