#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "myscene.h"
//#include "mainwindow2.ui"
//#include <QGraphicsScene>
//#include <QGraphicsView>
//#include <QGraphicsRectItem>
//#include <QMouseEvent>
//#include <QWidget>
//#include <QPushButton>

class MainWindow : public QMainWindow//, QWidget
{
    Q_OBJECT

protected:
   // double itemRotation = -90;
  //  QKeyEvent *event = nullptr;

  // void changeRotation(QKeyEvent *event);
//    void changeRotation();
   // void mouseMoveEvent(QMouseEvent *myMouseEvent);
 //   void onMouseEvent();

public:
    MainWindow(MyScene *parent);
   // MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

};

#endif // MAINWINDOW_H
