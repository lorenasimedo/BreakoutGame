#include <QPainter>
#include <QApplication>
#include "breakout.h"
#include <QDebug>
#include <QString>
#include <QFont>
#include <iostream>

Breakout::Breakout(QWidget *parent)
    : QWidget(parent) {
  setFixedSize(500, 420);
  x = 0;
  gameOver = false;
  telaInformativa = false;
  gameWon = false;
  perdeuVida = false;
  showInformation=false;
  makeDelay=false;
  paused = true;
  gameStarted = true;
  ball = new Ball();
  paddle = new Paddle();
  numeroTijolos = N_OF_BRICKS;
  numeroBolas = 5;
  TimerActive = false;


  int k = 0;

  for (int i=0; i<5; i++) {
    for (int j=0; j<6; j++) {
      bricks[k] = new Brick(j*40+35, i*10+50);
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
    telaInformativa = true;
    printMessage(&painter, "Você perdeu!","");

  } else if(gameWon) {
    reiniciarBolas();
    telaInformativa = true;
    printMessage(&painter, "Vitória!","");
  } else if(perdeuVida){
    telaInformativa = true;
    printMessage(&painter, "Perdeu uma vida!","");
    perdeuVida = false;
  } else if(showInformation){
      QString message="Número de Tijolos:"+QString::number(numeroTijolos);
      QString message2="Número de Bolas:"+QString::number(numeroBolas);
      printMessage(&painter, message,message2);
  }else {
    telaInformativa = false;
    drawObjects(&painter);
  }
}



void Breakout::printMessage(QPainter *painter, QString message, QString message2) {

  QFont font("Courier", 15, QFont::DemiBold);
  QFontMetrics fm(font);
  int textWidth = fm.width(message);
  int textWidth2 = fm.width(message2);

  painter->setFont(font);
  int h = height();
  int w = width();

  painter->translate(QPoint(w/2, h/2));

  if(message2!=""){
      painter->drawText(-textWidth/2, -15, message);
      painter->drawText(-textWidth2/2, 15, message2);
  }else{
      painter->drawText(-textWidth/2, 0, message);
  }
}


void Breakout::atualizarAtributos(QPainter *painter){
    QPen pen(Qt::black, 1);
    QPen pen2(Qt::black, 2);
    painter->setPen(pen);
    QString quantidadeVidas;
    QString quantidadeTilojos;
    quantidadeVidas = "Bolas: " + QString::number(numeroBolas);
    quantidadeTilojos = "Tijolos: " + QString::number(numeroTijolos);
    QFont font("Times", 11, QFont::Bold);
    QPoint xyBola(340,150);
    QPoint xyTijolos(340,170);
    painter->setFont(font);
    painter->drawText(xyBola,quantidadeVidas);
    painter->drawText(xyTijolos,quantidadeTilojos);
    painter->setPen(pen2);
    int xAtributos = xyBola.x() - 10;
    int yAtributos = 130;
    painter->drawRect(xAtributos,yAtributos,90,50);

}

void Breakout::drawObjects(QPainter *painter) {
  int yRetangulo = BOTTOM_EDGE - TOP_EDGE;
  int xRetangulo = RIGHT_EDGE - LEFT_EDGE;
  QPen pen(Qt::black, 2);
  painter->setPen(pen);
  painter->drawRect(LEFT_EDGE,TOP_EDGE,xRetangulo,yRetangulo);
  painter->setPen(Qt::NoPen);
  painter->drawImage(ball->getRect(), ball->getImage());
  painter->drawImage(paddle->getRect(), paddle->getImage());

  atualizarAtributos( painter);


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
  if(makeDelay){
      pauseGame();
      showInformation=true;
      makeDelay=false;
      repaint();
  }
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
        showInformation=false;
        break;
    case Qt::RightButton:
        if(!paused){
            pauseGame();
            showInformation=true;
            repaint();
        }else{
            pauseGame();
            showInformation=false;
            repaint();
            makeDelay=true;
        }
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

    case Qt::Key_R:

        resetGame();
        break;

    case Qt::Key_Q:

        qApp->exit();
        break;

    default:
        QWidget::keyPressEvent(e);
    }
}

void Breakout::restartGame() {

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
    if (!TimerActive){
        timerId = startTimer(DELAY);
        TimerActive=true;
    }
  }
}

void Breakout::resetGame() {
    ball->resetState();
    ball->setXDir(1);
    ball->setYDir(-1);
    paddle->resetState();
    for (int i=0; i<N_OF_BRICKS; i++) {
      bricks[i]->setDestroyed(false);
    }
    numeroBolas = 5;
    numeroTijolos = N_OF_BRICKS;
    gameOver = false;
    gameWon = false;
    gameStarted = true;
    telaInformativa = false;
    perdeuVida = false;
    if(TimerActive){
        killTimer(timerId);
        TimerActive=false;
    }
    repaint();
    paused = true;
}

void Breakout::pauseGame() {

  if(telaInformativa){
        restartGame();
  } else if (paused) {
    if (!TimerActive){
        timerId = startTimer(DELAY);
        TimerActive=true;
    }
    paused = false;
  } else {

    paused = true;
    if(TimerActive){
        killTimer(timerId);
        TimerActive=false;
    }
  }
}

void Breakout::stopGame() {

  if(TimerActive){
      killTimer(timerId);
      TimerActive=false;
  }
  if(numeroBolas==0){
    gameOver = true;
    gameStarted = false;
  }else{
    gameOver = false;
    gameStarted = false;

  }
}

void Breakout::victory() {

  if(TimerActive){
      killTimer(timerId);
      TimerActive=false;
  }
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
