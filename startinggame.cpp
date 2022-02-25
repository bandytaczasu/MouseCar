#include "startinggame.h"
#include <QDebug>

StartingGame::StartingGame()
{
    startNewGame(true);
}

int StartingGame::startNewGame(bool wasEscapePressed)
{
    ConnectionClass *myConnection = new ConnectionClass();
    //startNewGame(false);
    MyScene *startScene = new MyScene();
    startTimer = new QTimer();

    QObject::connect(startScene, &MyScene::escapePressed,[=]() mutable {
        qDebug() << "Escape pressed";
//        delete  startScene;
        });

    QObject::connect(startTimer, &QTimer::timeout,[=]() mutable {
        startGameEscamePresed = myConnection->connectionEscape;
        endGame(startGameEscamePresed, startScene, myConnection);
       // delete  startScene;
        });

    startTimer->start(15);

    return 0;
}

int StartingGame::endGame(bool wasEscapePressed2, MyScene *endMyGane, ConnectionClass *endMyConnection)
{
    if (wasEscapePressed2 == false) { return  0; }
        else if (wasEscapePressed2 == true) {
        qDebug() << "Escape pressed";
//        delete endMyGane;
        delete endMyConnection;
        delete endMyGane;
        return 1;
    }
    return 0;
}
