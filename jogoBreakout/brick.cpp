#include <iostream>
#include "brick.h"

Brick::Brick(int x, int y) {
  image.load("/home/lorena/BreakoutGame/jogoBreakout/brickie.png");

  int inputWidth = 40;
  int inputHeight = 8;
  image = image.scaled(inputWidth, inputHeight,Qt::IgnoreAspectRatio);

  destroyed = false;
  rect = image.rect();
  rect.translate(x, y);
}

Brick::~Brick() {

  std::cout << ("Brick deleted") << std::endl;
}

QRect Brick::getRect() {

  return rect;
}

void Brick::setRect(QRect rct) {

  rect = rct;
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
