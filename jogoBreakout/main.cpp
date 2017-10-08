#include <QApplication>
#include "breakout.h"

int main(int argc, char *argv[]) {

  QApplication app(argc, argv);

  Breakout window;

  //window.resize(300, 400);
  window.setWindowTitle("Breakout - O jogo");
  window.show();

  return app.exec();
}
