#ifndef MOJEOKNO_H
#define MOJEOKNO_H

#include <QMainWindow>
#include "myscene.h"

namespace Ui {
class MojeOkno;
}

class MojeOkno : public QMainWindow, QGraphicsScene
{
public:
    MojeOkno(QGraphicsScene *parent);

private:
    Ui::MojeOkno *ui;
};

#endif // MOJEOKNO_H
