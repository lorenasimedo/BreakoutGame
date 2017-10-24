#include <iostream>
#include "ball.h"

Ball::Ball() {

  xdir = 1;
  ydir = -1;

  image.load("../jogoBreakout/ball.png");

  int inputWidth = 15;
  int inputHeight = 15;
  image = image.scaled(inputWidth, inputHeight,Qt::IgnoreAspectRatio);

  rect = image.rect();
  resetState();
}

Ball::~Ball() {

  std::cout << ("Ball deleted") << std::endl;
}

void Ball::autoMove() {

  rect.translate(xdir, ydir);

  if (rect.left() == LEFT_EDGE) {
    xdir = 1;
  }

  if (rect.right() == RIGHT_EDGE) {
    xdir = -1;
  }

  if (rect.top() == TOP_EDGE) {
    ydir = 1;
  }
}

void Ball::resetState() {
  rect.moveTo(INITIAL_X, INITIAL_Y);
}

int Ball::eixoX() {
  posicaoX = rect.x();
  return posicaoX;
}

int Ball::eixoY() {
  posicaoY = rect.y();
  return posicaoY;
}

void Ball::setXDir(int x) {

  xdir = x;
}

void Ball::setYDir(int y) {

  ydir = y;
}

int Ball::getXDir() {

  return xdir;
}

int Ball::getYDir() {

  return ydir;
}

QRect Ball::getRect() {

  return rect;
}

QImage & Ball::getImage() {

  return image;
}
