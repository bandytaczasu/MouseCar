#ifndef STARTINGGAME_H
#define STARTINGGAME_H

#include "connectionclass.h"
#include "myscene.h"
#include <QTimer>

class StartingGame {

public:
    StartingGame();

   // ~StartingGame();

//protected:
    int startNewGame(bool wasEscapePressed);
    int endGame(bool wasEscapePressed2, MyScene *endMyGane, ConnectionClass *endMyConnection);

  //  MyScene *startScene = new MyScene();

private:
    QTimer *startTimer;
    bool startGameEscamePresed = false;

};

#endif // STARTINGGAME_H
