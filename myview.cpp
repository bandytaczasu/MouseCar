#include "myscene.cpp"
#include <QDebug>
#include <QLabel>
#include <QTime>

MyView::MyView(MyScene *someScene)
{
    this->setScene(someScene);
    this->QWidget::setMouseTracking(true);
    this->setCursor(Qt::BlankCursor);

    QScrollBar *horizBar = this->horizontalScrollBar();
    QScrollBar *vertBar = this->verticalScrollBar();
    horizBar->hide();
    vertBar->hide();

    timeCounter = new QLabel(this);
    timeCounter->setVisible(false);

    checkpointSign = new QLabel(this);
    checkpointSign->setVisible(false);

    welcomeSign = new QLabel(this);
   // welcomeSign->setVisible(true);

    resultTime= new QLabel(this);
    resultTime->setVisible(true);


    myTime = new QTime(00, 00, 00, 00);
    QTimer *scrollTimer = new QTimer;
    QTimer *timerTimer = new QTimer;
    courseTimer = new QTimer();

    timeCounter->setText(myTime->toString());

    checkSignTime = new QTimer();
    resultSignTime = new QTimer();

    this->setTransformationAnchor(QGraphicsView::NoAnchor);

  //  this->centerOn(someScene->myPos);

    connect(someScene->myTimer, SIGNAL(timeout()), this, SLOT(setCourseTimer()));
//    connect(someScene, SIGNAL(checkSignTransfer()), this, SLOT(displayCheckpointSign()));
    connect(someScene, SIGNAL(checkSignTransfer()), this, SLOT(checkpointSlot()));
   // connect(someScene, SIGNAL(transferLapSignal()), this, SLOT(increaseLapsNumber()));
    connect(someScene, SIGNAL(sceneStartCrossed()), this, SLOT(startTimer()));
    connect(courseTimer, SIGNAL(timeout()), this, SLOT(increaseTimer()));
    connect(someScene, SIGNAL(braking()), this, SLOT(removeWelcomeSign()));
    connect(scrollTimer, &QTimer::timeout,[=]() mutable {
            QPointF newPoint = someScene->myPos;
            this->centerOn(newPoint);
            timerTimer = someScene->myTimer;
            lapNumber = someScene->transferLaps;
            if (spacePressed == false) {
                displayWelcomeSign(true); } else if (spacePressed == true) {
                welcomeSign->setVisible(false);
            }
        });

    scrollTimer->start(0.5);


    MyScene *scene = new MyScene();
    QPointF currScenePos = sceneRect().center();

}

void MyView::increaseTimer()
{
    *myTime = myTime->addSecs(1);

}

void MyView::carScrolling()
{
    qDebug() << "Foo";
}

void MyView::startTimer()
{
    QString startSign;
    courseTimer->start(10);
    if (lapNumber <= 0) {
    startSign = "START";
    } else { startSign = QStringLiteral("LAP %1").arg(lapNumber); }
    int startX = 50;
    displayCheckpointSign(startSign, true, startX);
    if (lapNumber >= 3) {
        resultTime->setText(myTime->toString());
        QString resultSign = "YOUR TIME IS: "; //, resultTime;
        int resultSignX = 250;
        displayCheckpointSign(resultSign, false, resultSignX);
        displayResult();
    }
}

void MyView::setCourseTimer()
{
    timeCounter->resize(500, 50);
    timeCounter->setFrameStyle(QFrame::NoFrame);
    timeCounter->move(this->width()-200, 100);
    QFont timeFont("Arial", 30, QFont::Bold);
   // timeCounter->setVisible(true);
    timeCounter->setFont(timeFont);
    timeCounter->setText(myTime->toString());
   // timeCounter->move(this->width()-200, 100);
    timeCounter->setVisible(true);
}

bool MyView::displayResultSign()
{
    if (lapNumber >= 1) {
        resultTime->setText(myTime->toString());
        QString checkPSign = "YOUR TIME IS: ", resultTime;
        int checkSignX = 250;
        displayCheckpointSign(checkPSign, false, checkSignX);
        return true;
      //  resultTime->setText(myTime->toString());
    } else
        return false;
}

void MyView::displayResult()
{

    resultTime->resize(500, 50);
    resultTime->setFrameStyle(QFrame::NoFrame);
  //  resultTime->move(this->width()-300, 100);
    resultTime->move(700, 100);
    QFont timeFont("Arial", 30, QFont::Bold);
   // timeCounter->setVisible(true);
    resultTime->setFont(timeFont);
    resultTime->setVisible(true);

}

void MyView::displayCheckpointSign(QString mySign, bool resultCheckpoint, int myXCoord)
{
    checkpointSign->resize(500, 50);
    checkpointSign->setFrameStyle(QFrame::NoFrame);
//    checkpointSign->move(50, 100);
    checkpointSign->move(myXCoord, 100);
    QFont checkpointFont("Arial", 30, QFont::Bold);
    checkpointSign->setFont(checkpointFont);
//    checkpointSign->setText("CHECKPOINT");
    checkpointSign->setText(mySign);
    checkpointSign->setVisible(true);
    checkSignTime->start(1000);
    if (resultCheckpoint == true) {
    QObject::connect(checkSignTime, &QTimer::timeout,[=]() mutable {
        checkpointSign->setVisible(false);
    });
    } else if (resultCheckpoint == false) { QObject::connect(checkSignTime, &QTimer::timeout,[=]() mutable {
            checkpointSign->setVisible(true);
        }); }
}

void MyView::displayStart()
{


}

void MyView::displayLaps()
{

}

void MyView::displayTimer()
{


}

void MyView::displayWelcomeSign(bool signVisible)
{
    welcomeSign->resize(550, 50);
    welcomeSign->setFrameStyle(QFrame::NoFrame);
    welcomeSign->move(100, 200);
    QFont checkpointFont("Arial", 20, QFont::Bold);
    welcomeSign->setFont(checkpointFont);
    QString welcomeSignWording = "PRESS SPACE TO START, ESC TO END";
    welcomeSign->setText(welcomeSignWording);
    welcomeSign->setVisible(signVisible);

}

void MyView::checkpointSlot()
{
    QString checkPSign = "CHECKPOINT";
    int checkSignX = 50;
    displayCheckpointSign(checkPSign, true, checkSignX);

}

void MyView::increaseLapsNumber()
{
    lapNumber = lapNumber + 1;

}

void MyView::removeWelcomeSign()
{
    spacePressed = true;
    qDebug() << "Remove welcome sign";

}
