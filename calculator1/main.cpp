#include "widget.h"
#include "mortgage.h"
#include "QDebug"
#include <QApplication>

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  Widget w;
  w.show();
  return a.exec();
}
