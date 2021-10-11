#ifndef LEVEL_H
#define LEVEL_H

#include <QWidget>
#include "mylabel.h"
#include <QPair>

const int  WIDTH = 450;
const int HEIGHT = 800;

namespace Ui {
class Level;
}

class Level : public QWidget
{
  Q_OBJECT

public:
  explicit Level(int levelNum, QWidget *parent = nullptr);
  ~Level();

private:
  Ui::Level *ui;
};

#endif // LEVEL_H
