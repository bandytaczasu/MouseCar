#include "connectionclass.h"
#include "mojeokno.cpp"


ConnectionClass::ConnectionClass()
{
    MyScene *anotherScene = new MyScene();
    MyView *anotherView = new MyView(anotherScene);
    MyRect *anotherRect = new MyRect();
    MojeOkno *newWindow = new MojeOkno(anotherScene);

    QPointF *connectPos = new QPointF();
    QObject::connect(anotherScene, SIGNAL(ForwardWasPressed()), anotherRect, SLOT(ForwardWasPressed()));
    QObject::connect(anotherScene, &MyScene::escapePressed,[=]() mutable {
      //  qDebug() << "connection escape";
      //  sendEscSign();
        connectionEscape = true;
    });


    anotherView->show();

}

void ConnectionClass::sendEscSign()
{
    //emit ConnectEscPress();

}
