#include <QPainter>
#include <QApplication>
#include "breakout.h"
#include <QDebug>

Breakout::Breakout(QWidget *parent)
    : QWidget(parent) {
  setFixedSize(500, 400);
  x = 0;
  gameOver = false;
  gameWon = false;
  perdeuVida = false;
  paused = true;
  gameStarted = true;
  ball = new Ball();
  paddle = new Paddle();
  numeroTijolos = N_OF_BRICKS;
  numeroBolas = 5;


  int k = 0;

  for (int i=0; i<5; i++) {
    for (int j=0; j<6; j++) {
      bricks[k] = new Brick(j*40+30, i*10+50);
      k++;
    }
  }
}

Breakout::~Breakout() {

 delete ball;
 delete paddle;

 for (int i=0; i<N_OF_BRICKS; i++) {
   delete bricks[i];
 }
}

void Breakout::reiniciarBolas(){
    numeroBolas = 5;
}



void Breakout::paintEvent(QPaintEvent *e) {

  Q_UNUSED(e);

  QPainter painter(this);

  if (gameOver) {
    reiniciarBolas();
    perdeuVida = false;
    finishGame(&painter, "Você perdeu!");

  } else if(gameWon) {
    reiniciarBolas();
    finishGame(&painter, "Vitória!");
  } else if(perdeuVida){
    finishGame(&painter, "Perdeu uma vida!");
    perdeuVida = false;
  }  else {
    drawObjects(&painter);
  }
}



void Breakout::finishGame(QPainter *painter, QString message) {

  QFont font("Courier", 15, QFont::DemiBold);
  QFontMetrics fm(font);
  int textWidth = fm.width(message);

  painter->setFont(font);
  int h = height();
  int w = width();

  painter->translate(QPoint(w/2, h/2));
  painter->drawText(-textWidth/2, 0, message);
}

void Breakout::drawObjects(QPainter *painter) {

  painter->drawImage(ball->getRect(), ball->getImage());
  painter->drawImage(paddle->getRect(), paddle->getImage());

  for (int i=0; i<N_OF_BRICKS; i++) {
    if (!bricks[i]->isDestroyed()) {
      painter->drawImage(bricks[i]->getRect(), bricks[i]->getImage());
    }
  }
}

void Breakout::timerEvent(QTimerEvent *e) {

  Q_UNUSED(e);

  moveObjects();
  checkCollision();
  repaint();
}

void Breakout::moveObjects() {

  ball->autoMove();
  paddle->move();
}

void Breakout::keyReleaseEvent(QKeyEvent *e) {

    int dx = 0;

    switch (e->key()) {
        case Qt::Key_Left:
            dx = 0;
            paddle->setDx(dx);
            break;

        case Qt::Key_Right:
            dx = 0;
            paddle->setDx(dx);
            break;
    }
}

void Breakout::mousePressEvent(QMouseEvent *event){

    switch (event->button()) {
    case Qt::LeftButton:
        pauseGame();
        break;
    default:
        QWidget::mousePressEvent(event);

    }

}



void Breakout::keyPressEvent(QKeyEvent *e) {

    int dx = 0;

    switch (e->key()) {
    case Qt::Key_Left:

        dx = -1;
        paddle->setDx(dx);

        break;

    case Qt::Key_Right:

        dx = 1;
        paddle->setDx(dx);
        break;

    case Qt::Key_Space:

        startGame();
        break;

    case Qt::Key_Q:

        qApp->exit();
        break;

    default:
        QWidget::keyPressEvent(e);
    }
}

void Breakout::startGame() {

  if (!gameStarted) {
    ball->resetState();
    paddle->resetState();

    for (int i=0; i<N_OF_BRICKS; i++) {
      bricks[i]->setDestroyed(false);
    }
    numeroTijolos = N_OF_BRICKS;
    gameOver = false;
    gameWon = false;
    gameStarted = true;
    timerId = startTimer(DELAY);
  }
}

void Breakout::pauseGame() {

  if (paused) {

    timerId = startTimer(DELAY);
    paused = false;
  } else {

    paused = true;
    killTimer(timerId);
  }
}

void Breakout::stopGame() {

  killTimer(timerId);
  if(numeroBolas==0){
    gameOver = true;
    gameStarted = false;
  }else{
    gameOver = false;
    gameStarted = false;

  }
}

void Breakout::victory() {

  killTimer(timerId);
  gameWon = true;
  gameStarted = false;
}

void Breakout::checkCollision() {

  if (ball->getRect().bottom() > BOTTOM_EDGE) {
    numeroBolas--;
    perdeuVida = true;
    stopGame();
  }

  for (int i=0, j=0; i<N_OF_BRICKS; i++) {

    if (bricks[i]->isDestroyed()) {
      j++;
    }

    if (j == N_OF_BRICKS) {
      victory();
    }
  }

  if ((ball->getRect()).intersects(paddle->getRect())) {

    int paddleLPos = paddle->getRect().left();
    int ballLPos = ball->getRect().left();

    int first = paddleLPos + 8;
    int second = paddleLPos + 16;
    int third = paddleLPos + 24;
    int fourth = paddleLPos + 32;

    if (ballLPos < first) {
      ball->setXDir(-1);
      ball->setYDir(-1);
    }

    if (ballLPos >= first && ballLPos < second) {
      ball->setXDir(-1);
      ball->setYDir(-1*ball->getYDir());
    }

    if (ballLPos >= second && ballLPos < third) {
       ball->setXDir(0);
       ball->setYDir(-1);
    }

    if (ballLPos >= third && ballLPos < fourth) {
       ball->setXDir(1);
       ball->setYDir(-1*ball->getYDir());
    }

    if (ballLPos >= fourth) {
      ball->setXDir(1);
      ball->setYDir(-1);
    }
  }

  for (int i=0; i<N_OF_BRICKS; i++) {

    if ((ball->getRect()).intersects(bricks[i]->getRect())) {

      int ballLeft = ball->getRect().left();
      int ballHeight = ball->getRect().height();
      int ballWidth = ball->getRect().width();
      int ballTop = ball->getRect().top();


      QPoint pointRight(ballLeft + ballWidth + 1, ballTop);
      QPoint pointLeft(ballLeft - 1, ballTop);
      QPoint pointTop(ballLeft, ballTop -1);
      QPoint pointBottom(ballLeft, ballTop + ballHeight + 1);

      if (!bricks[i]->isDestroyed()) {
        if(bricks[i]->getRect().contains(pointRight)) {
           ball->setXDir(-1);
        }

        else if(bricks[i]->getRect().contains(pointLeft)) {
           ball->setXDir(1);
        }

        if(bricks[i]->getRect().contains(pointTop)) {
           ball->setYDir(1);
        }

        else if(bricks[i]->getRect().contains(pointBottom)) {
           ball->setYDir(-1);
        }
        numeroTijolos--;
        bricks[i]->setDestroyed(true);
        qDebug()<<"Numero de Tijolos:"<<numeroTijolos;
        qDebug()<<"Numero de Bolas:"<<numeroBolas;
      }
    }
  }
}
