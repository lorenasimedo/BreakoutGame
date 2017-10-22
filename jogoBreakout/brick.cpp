#include <iostream>
#include "brick.h"

Brick::Brick(int x, int y) {
  vida = 2;
  image.load("../jogoBreakout/primeirobrickie.png");
  int inputWidth = 35;
  int inputHeight = 8;
  image = image.scaled(inputWidth, inputHeight,Qt::IgnoreAspectRatio);
  destroyed = false;
  rect = image.rect();
  rect.translate(x, y);
}

Brick::~Brick() {

}

QRect Brick::getRect() {
  return rect;

}

void Brick::diminuirVidas() {
  image.load("../jogoBreakout/brickie.png");
  vida--;
}
int Brick::numeroVidas() {
  return vida;
}


void Brick::setRect(QRect rct) {

  rect = rct;
}

void Brick::setVidas(int vidas) {
  image.load("../jogoBreakout/primeirobrickie.png");
  vida = vidas;
}

QImage & Brick::getImage() {
   return image;
}


bool Brick::isDestroyed() {
    return destroyed;
}

void Brick::setDestroyed(bool destr) {

  destroyed = destr;
}
