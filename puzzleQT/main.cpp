#include "mainwindow.h"

#include <QApplication>
#include <QLabel>
#include <QPainter>
#include <QList>
#include "success.h"

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  MainWindow w;
  w.setWindowTitle("puzzle");
  w.show();
  return a.exec();
}
