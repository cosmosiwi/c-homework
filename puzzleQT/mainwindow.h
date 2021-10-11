#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "success.h"

#include <QMainWindow>
#include <level.h>
#include <QPair>
#include <algorithm>
#include <QMap>

#include <QTime>
#include <QTimer>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

  void selectLevel(int levelNum);

private slots:
  /***************************************
   * 先用pushbutton实现计时器的功能，随后再改？
   * 鼠标点击图片开始计时
   * *************************************/

  //更新时间
  void updateTime();


private:
  Ui::MainWindow *ui;
  Level *level = nullptr;
  const int NONE = 1<<21;
  int clickFront = NONE;
  int levelNum = 3;
  QList<QPair<MyLabel* , QPixmap> > labList;
  void labClickedLogic(int idNum);
  void resetLogic(int levelNum);
  void showIcon(int levelNum);
  void selectLogic();
  QVector<int> in_ord;

  //响应鼠标事件
  bool isClicked = false;
  //计时器
  QTimer *pTimer;
  QTime baseTime;
  //显示时间的字符串
  QString timeStr;
  //初始化
  void init();

  //check
  QMap<MyLabel*, int> in_order;
  bool check();
  Success s;
};
#endif // MAINWINDOW_H
