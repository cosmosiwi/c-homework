#ifndef MORTGAGE_H
#define MORTGAGE_H

#include <QWidget>

namespace Ui {
class Mortgage;
}

class Mortgage : public QWidget
{
  Q_OBJECT

public:
  explicit Mortgage(QWidget *parent = nullptr);
  ~Mortgage();

private slots:
  void on_pushButton_clicked();

  void on_pushButton_2_clicked();

private:
  Ui::Mortgage *ui;
};

#endif // MORTGAGE_H
