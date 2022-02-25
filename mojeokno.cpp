#include "ui_mojeokno.h"
#include "mojeokno.h"
#include "myrect.h"

MojeOkno::MojeOkno(QGraphicsScene *parent) : ui(new Ui::MojeOkno) {
     ui->setupUi(this);
   //  this->setSceneRect(100, 100, 400000, 400000);
    // this->addWidget(parent);
     MyRect *oknoRect = new MyRect();
     this->addItem(oknoRect);
     oknoRect->setPos(100, 100);
     oknoRect->setFlag(QGraphicsItem::ItemIsMovable, true);
     oknoRect->setRotation(oknoRect->initAngle-30);
     oknoRect->currentAngle = oknoRect->rotation();
     oknoRect->posX = oknoRect->pos().x();
     oknoRect->posY = oknoRect->pos().y();
     oknoRect->rotatingWithMouse();
     const QRectF &newRect = QRectF();
     oknoRect->ensureVisible(newRect, 5000, 5000);
   //  parent->
}
