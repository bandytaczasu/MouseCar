/*
 * Author: Łukasz Słonecki
 * All graphics and sounds are from OpenGameArt.org
 *
 * Car is from Telefrag Entertainment
 * https://opengameart.org/content/cars-trucks-and-a-limo
 *
 * Road is from CraftPix.net 2D Game Assets
 * https://opengameart.org/content/race-track-tile-set
 *
 * Sounds are from Nayckron
 * https://opengameart.org/content/engine-loop-heavy-vehicletank
*/


#include "startinggame.h"
#include <QApplication>

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);

   // ConnectionClass *myConClass = new ConnectionClass();
    StartingGame *startGame = new StartingGame();

    return a.exec();
}
