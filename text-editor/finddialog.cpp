#include "finddialog.h"
#include "QDebug"
#include "mainwindow.h"


FindDialog::FindDialog(QWidget *parent) :
    QDialog(parent)
{
    this->setWindowTitle("Search");

    QHBoxLayout *hbox = new QHBoxLayout;
    QLabel *lab = new QLabel;
    QPushButton *bt1=new QPushButton("search");
    lineedit=new QLineEdit;
    lab->setText("请输入您想要查找的内容：");
    hbox->addWidget(lab);
    hbox->addWidget(lineedit);
    hbox->addWidget(bt1);
    setLayout(hbox);

    // connect(bt1,SIGNAL(clicked(bool)),this,SLOT(search()));
    connect(bt1,&QPushButton::clicked,this,[=](){
      emitsearchSignal();
    });

}

FindDialog::~FindDialog()
{

}

void FindDialog::search()
{

}

void FindDialog::emitsearchSignal()
{
    QString str = lineedit->text();
    qDebug() << str;
    if(!str.isEmpty())
    {
        emit searchSignal(str);
    }
}

