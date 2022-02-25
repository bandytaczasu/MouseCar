#ifndef MYVIEW_H
#define MYVIEW_H

#include <QGraphicsView>
#include <QKeyEvent>
#include <QScrollBar>
#include <QObject>
#include "myscene.h"
#include <QLabel>

class MyView : public QGraphicsView
{
   Q_OBJECT

public:
    MyView(MyScene *someScene);

    QPointF newPos;

public slots:
    void increaseTimer();
    void carScrolling();
    void startTimer();
    void setCourseTimer();
//    void displayCheckpointSign();
    bool displayResultSign();
    void displayResult();
    void displayStart();
    void displayLaps();
    void displayTimer();
    void displayWelcomeSign(bool signVisible);
 //   void displayResult();
    void checkpointSlot();
    void increaseLapsNumber();
    void removeWelcomeSign();
   // void InitialCentering();

private:
    QLabel *timeCounter;
    QLabel *checkpointSign;
    QLabel *welcomeSign;
    QTime *myTime;
    QLabel *resultTime;
    QTimer *checkSignTime;
    QTimer *resultSignTime;
    QTimer *courseTimer;
    int lapNumber = 0;
    int intResult = 0;
    bool spacePressed = false;

    void displayCheckpointSign(QString mySign, bool resultCheckpoint, int myXCoord);

};


#endif // MYVIEW_H
