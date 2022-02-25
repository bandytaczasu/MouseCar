#ifndef MYRECT_H
#define MYRECT_H

#include <QGraphicsRectItem>
#include <QMouseEvent>
#include "myview.h"
#include <QObject>
#include <QColor>
//#include <QtMultimedia/QMediaPlayer>

class MyRect : public QObject, public QGraphicsRectItem
{
    Q_OBJECT
public:
    double myX = 0;
    double myY = 0;
    double someChange = 10;
    double myChange = 0;
    double initAngle = 0;
    double currentAngle;
    double posX;
    double posY;
    double driveWheel = 0;
    bool forwardPressed = false;
    double lengthX = 0;
    double lengthY = 0;
    bool viewFollow = true;
    int laps = 0;
    QPointF viewPos;
    QColor positionColor;

    MyRect();
    QPointF carPos();

protected:
    void rotationCorrection();

 signals:
    void carMoved();
    void startCrossed();
    void carIdle();
    void carAccelerates();
    void carCruises();
    void checkpointSignal();
    //void StartSignal();
    void lapSignal();

public slots:
    void rotatingWithMouse();
   // void ConsoleDebug();
    void isForwardPressedTrue();
    void moveForward(bool forward, bool backward);
    void moveBackward();
    void cursorChange();
    void initialRotation();
    void increaseCounter();
    void resetCounter();
    void forwardWasPressed();
    void backwardWasPressed();
    void decelTime();
    void forwardWasReleased();
    void braking();
    void setCarPosition();

private:
    double oldPos = 0;
    bool goForward = false;
    bool goBackward = false;
    bool standStill = true;
    bool alreadyGoingForward = false;
    bool alreadyGoingBackward = false;
    qreal changeDirection;
    double deceleration = 0;
    double rectCounter = 0;
    double accelCounter = 0;
    double accelTimer = 0;
    double driveWheelRotation = 0;
    double wheelTurn = 0;
    double pavementFactor = 0;
    bool startLineCrossed = false;
    bool checkpoint1Crossed = false;
    bool checkpoint2Crossed = false;
    bool checkpoint3Crossed = false;
    bool checkpoint4Crossed = false;
   // int laps = 0;
   // QMediaPlayer *engineSound = new QMediaPlayer;

    void accelTimeIncrease(bool signal1, bool signal2, bool direction1, bool direction2);
    void checkpointPassed(double checkPosX, double checkPosY);

};

#endif // MYRECT_H
