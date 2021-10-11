#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QStack>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
  Q_OBJECT

public:
  Widget(QWidget *parent = nullptr);
  ~Widget();
  void init();
  void connects();
  void getInfix();
  void calInfix(); // 计算后缀表达式

public slots:
  void pushButton1_clicked();
  void pushButton2_clicked();
  void pushButton3_clicked();
  void pushButton4_clicked();
  void pushButton5_clicked();
  void pushButton6_clicked();
  void pushButton7_clicked();
  void pushButton8_clicked();
  void pushButton9_clicked();
  void pushButton0_clicked();
  void pushButton_add_clicked();
  void pushButton_minus_clicked();
  void pushButton_mul_clicked();
  void pushButton_div_clicked();
  void pushButton_equal_clicked();
  void pushButton_delete_clicked();
  void pushButton_backspace_clicked();
  void pushButton_left_clicked();
  void pushButton_right_clicked();
  void pushButton_point_clicked();
  void pushButton_pow_clicked();

private:
  Ui::Widget *ui;
  QString in;
  QVector<QString> out;
  double result;
};
#endif // WIDGET_H
