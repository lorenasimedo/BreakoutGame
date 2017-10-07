#ifndef BREAKOUT_H
#define BREAKOUT_H

#include <QMainWindow>

namespace Ui {
class breakout;
}

class breakout : public QMainWindow
{
    Q_OBJECT

public:
    explicit breakout(QWidget *parent = 0);
    ~breakout();

private:
    Ui::breakout *ui;
};

#endif // BREAKOUT_H
