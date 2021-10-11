#include "success.h"
#include "ui_success.h"

Success::Success(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::Success)
{
  ui->setupUi(this);
  //connect(ui->exit, &QPushButton::clicked, this, SLOT(close()));
}

Success::~Success()
{
  delete ui;

}
