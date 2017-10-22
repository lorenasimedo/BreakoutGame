#include "level.h"

Level::Level()
{
    numeroLevel = 1;
    DELAY = inicialDELAY;
}


Level::~Level(){

}

int Level::levelAtual(){
    return numeroLevel;
}

void Level::passouLevel(){
    numeroLevel++;
    DELAY= DELAY/2;
}

void Level::reiniciarLevel(){
    numeroLevel = 1;
    DELAY = inicialDELAY;
}

int Level::retornaDELAY(){
    return DELAY;
}
