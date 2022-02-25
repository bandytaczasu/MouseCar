#ifndef MYSCENE_H
#define MYSCENE_H

#include <QGraphicsScene>
#include <QMainWindow>
#include <QMouseEvent>
#include <QWidget>
#include <QKeyEvent>
#include <iostream>
#include <QObject>
#include <QPixmap>
#include <QTimer>
#include <QPushButton>
#include <QtMultimedia/QMediaPlayer>
#include <QtMultimedia/QSound>

namespace Ui {
class Form;
}

class MyScene :  public QGraphicsScene
{
    Q_OBJECT

public:

    bool forwardPressed = false;
    bool backwardPressed = false;
    QTimer *myTimer;
    QTimer *decelTimer;
    QTimer *myScrollTimer;
    QTimer *courseTimer;
    QPushButton *myButton;
    int counter = 0;
    int transferLaps = 0;
    double pressTimeCounter = 0;
    QPointF myPos;
    double carPosChangeX = 0;
    double carPosChangeY = 0;
    QPointF viewPos;
    bool escapeWasPresed = false;

    MyScene();

    virtual ~MyScene();

signals:
    void mouseMoveEvent(QGraphicsSceneMouseEvent *myEvent);
    void forwardWasPressed();
    void backwardWasPressed();
    void goingForward();
    void goingBackward();
    void braking();
    void sceneStartCrossed();
    void signalEvent(QKeyEvent *myEvent);
 //   void MouseMoveEvent(QMouseEvent *myEvent = nullptr);
    void counterReset();
    void runEngineSound();
    void checkSignTransfer();
    void transferLapSignal();
    void escapePressed();

public slots:
    void newConsoleDebug();
    void isForwardPressed();
    void stillGoingForward();
    void stillGoingBackward();
    void standingStill();
    void newPost();
    void startCourseTimer();
    void emitStartCrossed();
   // void PlayEngineSound();
    void playCruiseSound();
    void playIdleSound();
    void playAccelSound();
    void setEngineRunning();
    void sendCheckSignal();
    void emitLapSignal();
   // void DisplaySi

protected:
   // QMediaPlayer *engineSound = new QMediaPlayer;
    QSound *cruisingSound;
    QSound *idleSound;
    QSound *accelSound;

    void keyPressEvent(QKeyEvent *keyEvent);
    void keyReleaseEvent(QKeyEvent *keyEvent);
    bool changeForwardPressed();
    bool changeBackwardPressed();

private:
    Ui::Form *myUi;
    bool stillForward = false;
    bool stillBackward = false;
    bool engineIsRunning = false;
//    bool escapeWasPresed = false;

    QTimer *engineSoundTimer;


};

#endif // MYSCENE_H
