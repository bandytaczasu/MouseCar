#include "mainwindow.h"
#include <QKeyEvent>
#include <QDebug>
#include <QMouseEvent>

MainWindow::MainWindow(MyScene *parent)
  //  : QMainWindow(parent)
{
  //  parent->
    this->setMouseTracking(true);
    MyScene *windowScene = new MyScene();
//    QGraphicsScene *scene = new QGraphicsScene();
//    //QGraphicsView *view = new QGraphicsView(scene);
//    QGraphicsRectItem *rect = new QGraphicsRectItem();
//    rect->setRect(0, 0, 100, 100);
//    rect->setTransformOriginPoint(50, 50);
//    rect->setRotation(itemRotation);
//    scene->addItem(rect);
//    rect->setFlag(QGraphicsItem::ItemIsFocusable);
//    rect->setFocus();
//    QGraphicsView *view = new QGraphicsView(scene);

//  //  QKeyEvent *myEvent = nullptr;
//  //  if (event->key() == Qt::Key_A) {
//   //     qDebug() << "Key pressed";
//      //  itemRotation = itemRotation - 10;

//  //  }

//    view->show();
  //  setMouseTracking(true);
}

//void MainWindow::changeRotation()
//{
//   // if (event->key() == Qt::Key_A) {
//     //   qDebug() << "Key pressed";
//    //    itemRotation = itemRotation - 10;

//        //   }
//}

/*void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
//    qDebug() << QString::number(myMouseEvent->pos().x());
//    qDebug() << QString::number(myMouseEvent->pos().y());
//    if (myMouseEvent->type() == QEvent::MouseMove)
//     {
//     //  QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(myMouseEvent);
//       //qDebug() << (QString("Mouse move (%1,%2)").arg(mouseEvent->pos().x()).arg(mouseEvent->pos().y()));
//        qDebug() << "Mouse moved";
//     }
//    else {
        qDebug() <<"Mouse not moved";
    //    }

    //onMouseEvent();
}*/

//void MainWindow::onMouseEvent()
//{
//    qDebug() << "Mouse moved";
//}

MainWindow::~MainWindow()
{

}
