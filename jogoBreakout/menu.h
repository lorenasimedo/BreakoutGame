#ifndef MENU_H
#define MENU_H

#include <QObject>
#include <QPushButton>

class Breakout;

class menu : public QPushButton
{
Q_OBJECT
public:
    menu(QWidget *parent = 0);
    ~menu();
};

#endif // MENU_H

