#include <iostream>
#include "brick.h"
#include <QDebug>

Brick::Brick(int x, int y , bool poder){
  vida = 2;
  blocoEspecial = poder;
  inicializarBomba(blocoEspecial);
  int inputWidth = 35;
  int inputHeight = 8;
  image = image.scaled(inputWidth, inputHeight,Qt::IgnoreAspectRatio);
  destroyed = false;
  rect = image.rect();
  rect.translate(x, y);
}

Brick::~Brick() {

}

bool Brick::verificarEspecial(){
    return blocoEspecial;
}

void Brick::receberID(int ID){
    identificador = ID;
}

void Brick::inicializarBomba(bool possuiPoder){
    if (possuiPoder){
        image.load("../jogoBreakout/bombabrickie.png");
    }else{
        image.load("../jogoBreakout/primeirobrickie.png");
    }
}

void Brick::desativarBomba(bool desativar){
    if (desativar){
        blocoEspecial = false;
    }
}

void Brick::ativarBomba(bool ativar){
    if (ativar){
        blocoEspecial = true;
    }
}




QRect Brick::getRect() {
  return rect;

}

void Brick::diminuirVidas() {
  image.load("../jogoBreakout/brickie.png");
  if(vida>0){
      vida--;
  }
  if(vida==0){
      setDestroyed(true);
  }
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
