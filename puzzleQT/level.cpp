#include "level.h"
#include "ui_level.h"
#include <QDebug>
#include "mylabel.h"

Level::Level(int levelNum, QWidget *parent) :
  QWidget(parent),
  ui(new Ui::Level)
{
  ui->setupUi(this);

}

Level::~Level()
{
  delete ui;
}
