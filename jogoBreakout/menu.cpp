#include "menu.h"
#include <QPushButton>

menu::menu(QWidget *pai):
    QPushButton(pai)
{
    setGeometry(330,340,100,40);
    setFocusPolicy(Qt::NoFocus);
    setText("Menu");
}

menu::~menu() {

}


