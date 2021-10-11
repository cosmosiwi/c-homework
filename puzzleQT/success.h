#ifndef SUCCESS_H
#define SUCCESS_H

#include <QWidget>

namespace Ui {
class Success;
}

class Success : public QWidget
{
  Q_OBJECT

public:
  explicit Success(QWidget *parent = nullptr);
  ~Success();

private:
  Ui::Success *ui;
};

#endif // SUCCESS_H
