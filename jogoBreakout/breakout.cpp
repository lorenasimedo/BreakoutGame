#include "breakout.h"
#include "ui_breakout.h"

breakout::breakout(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::breakout)
{
    ui->setupUi(this);
}

breakout::~breakout()
{
    delete ui;
}
