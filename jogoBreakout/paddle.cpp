#include <iostream>
#include "paddle.h"

Paddle::Paddle() {

  dx = 0;
  image.load("../jogoBreakout/paddle.png");

  int inputWidth = 80;
  int inputHeight = 15;
  image = image.scaled(inputWidth, inputHeight,Qt::IgnoreAspectRatio);

  rect = image.rect();
  resetState();
}

Paddle::~Paddle() {

 std::cout << ("Paddle deleted") << std::endl;
}

void Paddle::setDx(int x) {
  dx = x;
}

void Paddle::move() {

    int x = rect.x() + dx;
    int y = rect.top();

    if(x<RIGHT_EDGE && x>LEFT_EDGE){
        rect.moveTo(x, y);
    }
}

void Paddle::resetState() {

  rect.moveTo(INITIAL_X, INITIAL_Y);
}

QRect Paddle::getRect() {

  return rect;
}

QImage & Paddle::getImage() {

  return image;
}
