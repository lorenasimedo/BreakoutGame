#ifndef BRICK_H
#define BRICK_H

#pragma once

#include <QImage>
#include <QRect>
//#include <cstdlib>

class Brick {

  public:
    Brick(int, int, bool);
    ~Brick();

  public:
    bool isDestroyed();
    void setDestroyed(bool);
    void setVidas(int);
    void diminuirVidas();
    int numeroVidas();
    bool verificarEspecial();
    QRect getRect();
    void setRect(QRect);
    QImage & getImage();
    void receberID(int);
    void desativarBomba(bool);
    void ativarBomba(bool);
    void inicializarBomba(bool);

  private:
    QImage image;
    QRect rect;
    int vida;
    int identificador;
    bool blocoEspecial;
    bool destroyed;
};

#endif // BRICK_H
