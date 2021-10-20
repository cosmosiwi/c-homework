#include "mortgage.h"
#include "ui_mortgage.h"
#include "QDebug"

Mortgage::Mortgage(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::Mortgage)
{
  ui->setupUi(this);
  this->setWindowTitle("利息计算器");

}

Mortgage::~Mortgage()
{
  delete ui;
}

void Mortgage::on_pushButton_clicked()
{
    QString strYearNum = ui->lineEdit->text();
    double yearNum = strYearNum.toDouble();
    QString strSumNum = ui->lineEdit_2->text();
    double sumNum = strSumNum.toDouble();
    QString strPercent = ui->lineEdit_3->text();
    double percent = strPercent.toDouble();
    double ret = yearNum*sumNum*percent;
    QString str;

    qDebug() << yearNum << sumNum << strPercent;

    str= str.setNum(ret);
    ui->lineEdit_4->setText(str);
}

void Mortgage::on_pushButton_2_clicked()
{
    ui->lineEdit->clear();
    ui->lineEdit_2->clear();
    ui->lineEdit_3->clear();
    ui->lineEdit_4->clear();
}
