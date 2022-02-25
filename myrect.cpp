#include "myrect.h"
#include "myscene.h"
#include "myview.h"
#include <QDebug>
#include <QKeyEvent>
#include <QMouseEvent>
#include <QObject>
#include <QPixmap>
#include <QtMath>

MyRect::MyRect()
{
    setRect(0, 0, 24, 56);
    setTransformOriginPoint(15, 22.5);
    setFlag(QGraphicsItem::ItemIsFocusable);

    setFocus();
//    engineSound->setMedia(QUrl::fromLocalFile(":/Sounds/loop_5.wav"));
//    engineSound->setVolume(50);
}

QPointF MyRect::carPos()
{
    QPointF carPosition;
    carPosition = this->pos();
    return carPosition;
}

void MyRect::setCarPosition()
{
    qDebug() << posX << posY;
}

void MyRect::rotationCorrection()
{
    if (currentAngle == (360) || (currentAngle == (-360))) {
         currentAngle = 0;
    }
}

void MyRect::isForwardPressedTrue()
{
    qDebug() << "Forward true";
}

void MyRect::cursorChange()
{
    if ((accelTimer <= 0) && (rectCounter <= 0)) { myChange = 0; } else
        if ((accelTimer >= 0.01) || (rectCounter >= 0)) {
    double curPos = QCursor::pos().x(); double curPosY = QCursor::pos().y();

    if (curPos <= 50) { QCursor::setPos((curPos+600), 300); oldPos = oldPos+600; }
    if (curPos >= 1200) { QCursor::setPos((curPos-600), 300); oldPos = oldPos+600;}
    if ((curPosY <= 50) || (curPosY >= 600)) { QCursor::setPos(curPos, 300); }

    if ((alreadyGoingForward == true) && (alreadyGoingBackward == false)) {
        myChange = curPos - oldPos; } else if ((alreadyGoingBackward == true) && (alreadyGoingForward == false)) {
        myChange = (curPos - oldPos)*(-1);
    }
    oldPos = curPos;
      //   qDebug() << curPos << curPosY;
        }
}

void MyRect::initialRotation()
{
    currentAngle = rotation();
}

void MyRect::increaseCounter()
{
    if (rectCounter < 0) { rectCounter = 0; } else
        if (rectCounter >= 0) {
    rectCounter = rectCounter + 0.1;
        }
}

void MyRect::resetCounter()
{
    rectCounter = 0;
}

void MyRect::forwardWasPressed()
{
    if (alreadyGoingBackward == true) {
        goForward = false;
        goBackward = true;

        if (accelTimer > 0) {accelTimer = accelTimer-0.2; alreadyGoingBackward = true; } else if (accelTimer <= 0 ) {accelTimer = 0;  alreadyGoingBackward = false; standStill = true; }

        decelTime();

    } else if (alreadyGoingBackward == false) {
        goForward = true;
        goBackward = false;
        accelTimeIncrease(goForward, goBackward, alreadyGoingForward, alreadyGoingBackward);
        moveForward(goForward, goBackward);
    }
}

void MyRect::backwardWasPressed()
{
    if (alreadyGoingForward == true) {
        goForward = true;
        goBackward = false;
        if (accelTimer > 0) {accelTimer = accelTimer-0.2; alreadyGoingForward = true; } else if (accelTimer <= 0 ) {accelTimer = 0;  alreadyGoingForward = false; standStill = true; }

        decelTime();
    } else if (alreadyGoingForward == false) {
        goForward = false;
        goBackward = true;
        accelTimeIncrease(goForward, goBackward, alreadyGoingForward, alreadyGoingBackward);
        moveForward(goForward, goBackward);
    }
}

void MyRect::decelTime()
{
    if (accelTimer > 0) {
        accelTimer = accelTimer - 0.05;
    moveForward(goForward, goBackward);
    }
    if (accelTimer <= 0) { accelTimer = 0;}
}

void MyRect::forwardWasReleased()
{

}

void MyRect::braking()
{
    accelTimer = accelTimer - 2; if (accelTimer <= 0) {accelTimer = 0;}
    decelTime();
    if (accelTimer <= 0) {accelTimer = 0; standStill = true; }
}

void MyRect::accelTimeIncrease(bool signal1, bool signal2, bool direction1, bool direction2)
{
    if ((signal1 == true && direction2 == true) || (signal2 == true && direction1 == true))

       { accelTimer = accelTimer - 0.1;
            } else {

                accelTimer = accelTimer + 0.1;
                if (accelTimer >= 10) { accelTimer = 10; }
                if (accelTimer <= 0) { accelTimer = 0; }
                }

}

void MyRect::checkpointPassed(double checkPosX, double checkPosY)
{
    if ((checkPosX >= 330 && checkPosX <= 650) && (checkPosY >= 550 && checkPosY <= 620)) { emit startCrossed();
        if ((laps <= 0) || (checkpoint4Crossed = true)) {startLineCrossed = true; checkpoint4Crossed = false;
        qDebug() << "Start" << laps;
       // if ( laps <= 0) { emit StartSignal(); } else if (laps >= 1) { emit lapSignal(); }
        if (laps >= 1) { emit lapSignal(); }
        }
    }

    if ((checkPosX >= 1845 && checkPosX <= 2167) && (checkPosY >= 3550 && checkPosY <= 3620)) { //emit startCrossed();
        if (startLineCrossed == true) { checkpoint1Crossed = true;
       qDebug() << "Checkpoint 1";
       emit checkpointSignal(); }
    }

    if ((checkPosX >= 7100 && checkPosX <= 7160) && (checkPosY >= 3650 && checkPosY <= 3985)) { //emit startCrossed();
        if (checkpoint1Crossed == true) { checkpoint2Crossed = true;
        qDebug() << "Checkpoint 2";
        emit checkpointSignal(); }
    }

    if ((checkPosX >= 4932 && checkPosX <= 5000) && (checkPosY >= 1484 && checkPosY <= 1820)) { //emit startCrossed();
         if (checkpoint2Crossed == true) { checkpoint3Crossed = true;
         qDebug() << "Checkpoint 3";
         emit checkpointSignal();  }
    }

    if ((checkPosX >= 2940 && checkPosX <= 3010) && (checkPosY >= 337 && checkPosY <= 680)) { //emit startCrossed();
        if (checkpoint3Crossed == true) { checkpoint4Crossed = true;
        startLineCrossed = false;
        checkpoint1Crossed = false;
        checkpoint2Crossed = false;
        checkpoint3Crossed = false;
        laps = laps + 1;
        qDebug() << "Checkpoint 4";
        //checkpoint4Crossed = false;
        emit checkpointSignal();
        }
    }
}

void MyRect::rotatingWithMouse()
{
    double absoluteChange = qFabs(myChange);

    if ((absoluteChange < 2) && (absoluteChange >= 10)) {
        if ((myChange >= -2) && (myChange <= 0)) { myChange = -2; } else
            if ((myChange > 0) && (myChange <= 2)) { myChange = 2; } else {
                if (myChange <= -200) { myChange = -200; } else
                    if (myChange >= 200) { myChange = 200; }
        }

    } else
        if ((absoluteChange >= 2) && (absoluteChange < 10)) {

    double newDriveWheel = driveWheel + myChange;
    if (newDriveWheel >= 20) { newDriveWheel = 20; }
    if (newDriveWheel <= -20) { newDriveWheel = -20; }

    bool leftRight = ((driveWheel <= newDriveWheel) ? true : false);


    double myNewAngle = currentAngle + myChange;

    if ((myNewAngle >= 360)) { myNewAngle = 0; }
    if ((myNewAngle < 0)) { myNewAngle = 359; }
    double absoluteDiff = qFabs(myNewAngle-currentAngle);

    driveWheel = newDriveWheel;

        }
}

//void MyRect::ConsoleDebug()
//{
//    double rectCurPos = QCursor::pos().x();
//    qDebug() << "Console debug";

//}

void MyRect::moveForward(bool forward, bool backward)
{
//    engineSound = new QMediaPlayer;

    if (positionColor.blue() <= 50) { pavementFactor = 4; } else if
             (positionColor.blue() > 50) { pavementFactor = 1.5; }


    if (myChange <= -6) { myChange = -6; }
    if (myChange >= 6) { myChange = 6; }

    wheelTurn = wheelTurn + myChange;
    if (wheelTurn <= -27) { wheelTurn = -27; }
    if (wheelTurn >= 27) { wheelTurn = 27; }

    if ((wheelTurn <= 1.5) && (wheelTurn >= -1.5)) { wheelTurn = 0; }

    driveWheelRotation = currentAngle + (wheelTurn/(20/pavementFactor)*0.75);

    setRotation(driveWheelRotation);
    if ((driveWheelRotation <= -360) || (driveWheelRotation >= 360)) { driveWheelRotation = 0; } //else {
    currentAngle = driveWheelRotation;// }

    double oldPosX = posX;
    double oldPosY = posY;

    double posrotation = ((currentAngle) * (-1));

    posrotation = (posrotation * (3.14/180));

    if ((forward == true) && (backward == false)) {
    posX = (((posX) + (sin(posrotation))*(accelTimer/(pavementFactor*0.4))));
    posY = (((posY) + (cos(posrotation))*(accelTimer/(pavementFactor*0.4))));
    alreadyGoingForward = true; alreadyGoingBackward = false; standStill = false;
    rectCounter = accelTimer;
        } else if ((forward == false) && (backward == true)) {
        alreadyGoingForward = false; alreadyGoingBackward = true; standStill = false;
        if (alreadyGoingForward == true && alreadyGoingBackward == false) {accelTimer=accelTimer-1.5;} else
          //  if (alreadyGoingForward == false && alreadyGoingBackward == true) {qDebug()<<"four";}
        posX = (((posX) - (sin(posrotation))*(accelTimer/(pavementFactor*1))));
        posY = (((posY) - (cos(posrotation))*(accelTimer/(pavementFactor*1))));
        alreadyGoingForward = false; alreadyGoingBackward = true; standStill = false;
        rectCounter = accelTimer;
    }

    posrotation = 0;
    setPos(posX, posY);
    if (accelTimer <= 0) {
        standStill = true; alreadyGoingForward = false; alreadyGoingBackward = false;
    }

    emit carMoved();

    if (accelTimer <= 0) { emit carIdle(); }
    if ((accelTimer >= 1 && accelTimer <= 9)) { emit carAccelerates(); }
    if (accelTimer >= 10) { emit carCruises(); }

    lengthX = posX - oldPosX;
    lengthY = posY - oldPosY;

    if (lengthX >= 10000 ^ lengthY >= 10000) { posX = oldPosX; posY = oldPosY; }

    QPointF newPos = this->pos();

    viewFollow = false;

  //  if ((posX >= 330 && posX <= 650) && (posY >= 550 && posY <= 620)) { emit startCrossed(); }
    checkpointPassed(posX, posY);
  //  engineSound->play();

}

void MyRect::moveBackward()
{
    double driveWheelRotation = currentAngle + myChange;
    setRotation(driveWheelRotation);
    currentAngle = driveWheelRotation;
    double oldPosX = posX;
    double oldPosY = posY;

    lengthX = posX - oldPosX;
    lengthY = posY - oldPosY;

    double posrotation = ((currentAngle) * (-1));

    posrotation = (posrotation * (3.14/180));

    posX = (((posX) - (sin(posrotation))*4));
    posY = (((posY) - (cos(posrotation))*4));
    posrotation = 0;
    setPos(posX, posY);

    lengthX = posX - oldPosX;
    lengthY = posY - oldPosY;

}



