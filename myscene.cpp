#include <Windows.h>
#include <myscene.h>
#include <QDebug>
#include <QMouseEvent>
#include <QWidget>
#include "myrect.h"
#include <QGraphicsItem>
#include <QGraphicsSceneMouseEvent>
#include <QPainter>
#include <QBrush>
#include <QScrollArea>
#include <QPalette>
#include <QRgb>

MyScene::MyScene()
{
    this->setSceneRect(0, 0, 8000, 4000);
    MyRect *backGround = new MyRect();
    this->addItem(backGround);
    backGround->setPos(-1,-1);
    backGround->setRect(0, 0, 60000, 30000);
    QBrush backgroundBrush;
    QImage grass11 = QImage(":/Images/racetrack7.png"); // :/Images/clover.jpg
    backgroundBrush.setTextureImage(QImage(":/Images/racetrack7.png"));

    QScrollArea scrollArea;

    MyRect *rect = new MyRect();
    this->addItem(rect);
   // rect->setPos(480, 480);
    rect->setPos(100, 100);
    rect->setFlag(QGraphicsItem::ItemIsMovable, true);
   // rect->setRotation(rect->initAngle-30);
    rect->currentAngle = rect->rotation();
    rect->posX = rect->pos().x();
    rect->posY = rect->pos().y();
    rect->rotatingWithMouse();
    const QRectF &newRect = QRectF();
    rect->ensureVisible(newRect, 5000, 5000);

    QBrush brush;
    const QColor rectColor = Qt::transparent;

    brush.setColor(Qt::transparent);

    QPixmap rectBack(30, 45);
    rectBack.fill(Qt::transparent);
    QPainter myFiller(&rectBack);
    brush.color();
    brush.setTexture(rectBack);

    brush.setTextureImage(QImage(":/Images/car2_kopia.png")); //Telefrag Entertainment https://opengameart.org/content/cars-trucks-and-a-limo

    int angle = 45;

    backGround->setBrush(backgroundBrush);
    rect->setBrush(brush);
    int myWidth = 0;
    QPen borderPen(Qt::transparent);
    rect->setPen(borderPen);
    qreal initX = 100;
    qreal initY = 100;

    QGraphicsRectItem *startLine = new QGraphicsRectItem();
    startLine->setRect(330, 550, 310, 20);
    QPen startLineBorderPen(Qt::transparent);
    startLine->setPen(borderPen);
    this->addItem(startLine);

    myTimer = new QTimer();
    decelTimer = new QTimer();
    myScrollTimer = new QTimer();
    courseTimer = new QTimer();
    engineSoundTimer = new QTimer();
    engineSoundTimer->setInterval(10);


    accelSound = new QSound(":/Sounds/engine_heavy_average_loop.wav");
    cruisingSound = new QSound(":/Sounds/engine_heavy_fast_loop.wav");
    idleSound = new QSound(":/Sounds/engine_heavy_slow_loop.wav");

    connect(this, SIGNAL(mouseMoveEvent(QGraphicsSceneMouseEvent*)), rect, SLOT(cursorChange()));
    connect(myTimer, SIGNAL(timeout()), this, SLOT(isForwardPressed()));
    connect(this, SIGNAL(forwardWasPressed()), rect, SLOT(forwardWasPressed()));
    connect(this, SIGNAL(forwardWasPressed()), this, SLOT(startCourseTimer()));
    connect(this, SIGNAL(backwardWasPressed()), rect, SLOT(backwardWasPressed()));
    connect(this, SIGNAL(forwardWasPressed()), rect, SLOT(increaseCounter()));
    connect(this, SIGNAL(backwardWasPressed()), rect, SLOT(increaseCounter()));
    connect(this, SIGNAL(counterReset()), rect, SLOT(resetCounter()));
    connect(decelTimer, SIGNAL(timeout()), rect, SLOT(decelTime()));
    connect(this, SIGNAL(braking()), rect, SLOT(braking()));
    connect(rect, SIGNAL(carCruises()), this, SLOT(playCruiseSound()));
    connect(rect, SIGNAL(carIdle()), this, SLOT(playIdleSound()));
    connect(rect, SIGNAL(carAccelerates()), this, SLOT(playAccelSound()));
  //  connect(engineSoundTimer, SIGNAL(timeout()), engineSound, SLOT(play()));
    connect(rect, SIGNAL(startCrossed()), this, SLOT(emitStartCrossed()));
    connect(rect, SIGNAL(checkpointSignal()), this, SLOT(sendCheckSignal()));
    connect(rect, SIGNAL(lapSignal()), this, SLOT(emitLapSignal()));
    connect(rect, &MyRect::carMoved,[=](){
            QPointF oldMyPos = myPos;
            if (rect->viewFollow == true) {
                myPos = oldMyPos;
                } else { myPos.setX(rect->posX); myPos.setY(rect->posY);
                rect->viewFollow = true; }
            QImage image;
            QColor color = grass11.pixelColor(rect->posX, rect->posY);
            rect->positionColor = color;
            transferLaps = rect->laps;
        });

}

MyScene::~MyScene()
{

}

void MyScene::newConsoleDebug()
{
    qDebug() << "Something happened";
}

void MyScene::keyPressEvent(QKeyEvent *keyEvent)
{
      if ((keyEvent->key() == Qt::Key_W)&&(keyEvent->KeyPress)) {
          forwardPressed = true;
          changeForwardPressed();
          counter += counter + 1;
          decelTimer->stop();
       //   emit runEngineSound();
      }

      if ((keyEvent->key() == Qt::Key_S)&&(keyEvent->KeyPress)) {
          backwardPressed = true;
          changeBackwardPressed();
          counter += counter + 1;
          decelTimer->stop();
       //   emit runEngineSound();
      }

      if (keyEvent->key() == Qt::Key_Space) {
          if (myTimer->isActive() != true) { myTimer->start(15); } //else {
               emit braking(); //}
      }

      if (keyEvent->key() == Qt::Key_Escape) {
          emit escapePressed();
          escapeWasPresed = true;
      }
}

void MyScene::keyReleaseEvent(QKeyEvent *keyEvent)
{
    if ((keyEvent->key() == Qt::Key_W)&&(keyEvent->KeyRelease)) {
        if (keyEvent->isAutoRepeat() == false) {
        forwardPressed = false;
        counter = 0;
        emit counterReset();
        decelTimer->start(15);
        }
    }

    if ((keyEvent->key() == Qt::Key_S)&&(keyEvent->KeyRelease)) {
        if (keyEvent->isAutoRepeat() == false) {
        backwardPressed = false;
        counter = 0;
        emit counterReset();
        decelTimer->start(15);
        }
    }
}

bool MyScene::changeForwardPressed()
{
    return forwardPressed = true;
}

bool MyScene::changeBackwardPressed()
{
    return backwardPressed = true;
}

void MyScene::isForwardPressed()
{
    if (forwardPressed != false && forwardPressed == true) {
        emit forwardWasPressed();
        pressTimeCounter = pressTimeCounter + 0.1;
    } else {
        if (forwardPressed == false && forwardPressed != true) {
        }
    }

    if (backwardPressed != false && backwardPressed == true) {
        emit backwardWasPressed();
    } else {
        if (backwardPressed == false && backwardPressed != true) {
        }
    }
}

void MyScene::stillGoingForward()
{
    stillForward = true;
    stillBackward = false;
}

void MyScene::stillGoingBackward()
{
    stillForward = false;
    stillBackward = true;
    QObject::connect(this, SIGNAL(stillGoingForward()), this, SLOT(standingStill()));
}

void MyScene::standingStill()
{
    stillForward = false;
    stillBackward = false;
}

void MyScene::newPost()
{

}

void MyScene::startCourseTimer()
{
    courseTimer->start(10);

}

void MyScene::emitStartCrossed()
{
    emit sceneStartCrossed();

}

void MyScene::playCruiseSound()
{
    if (cruisingSound->isFinished() == true ) {
        idleSound->stop(); accelSound->stop();
        cruisingSound->play(); //i = i+1;
     }
}

void MyScene::playIdleSound()
{
    if (idleSound->isFinished() == true ) {
        cruisingSound->stop(); accelSound->stop();
        idleSound->play();
     }

}

void MyScene::playAccelSound()
{
    if (accelSound->isFinished() == true ) {
        cruisingSound->stop(); idleSound->stop();
        accelSound->play();
     }

}

void MyScene::setEngineRunning()
{
    engineIsRunning = true;
}

void MyScene::sendCheckSignal()
{
    emit checkSignTransfer();
}

void MyScene::emitLapSignal()
{
    emit transferLapSignal();
}
