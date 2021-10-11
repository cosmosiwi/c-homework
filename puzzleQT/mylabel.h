#ifndef MYLABEL_H
#define MYLABEL_H

#include <QMainWindow>
#include <QWidget>
#include <QLabel>

class MyLabel : public QLabel
{
  Q_OBJECT
public:
  explicit MyLabel(QWidget *parent = nullptr);
protected:
  //实现鼠标释放函数
  void mouseReleaseEvent(QMouseEvent *ev);
signals:
  void clicked();
};

#endif // MYLABEL_H
