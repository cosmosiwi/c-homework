#include "widget.h"
#include "QDebug"
#include "cmath"
#include "ui_widget.h"
#include "QToolBar"
#include "QStatusBar"
#include <QMainWindow>
#include "mortgage.h"

Widget::Widget(QWidget *parent)
  : QWidget(parent)
  , ui(new Ui::Widget)
{
  ui->setupUi(this);
  ui->lineEdit->setReadOnly(true);//只读模式
  //ui->lineEdit->move(QPoint(0,0));//设置lineEdit位置
  ui->lineEdit->setAlignment(Qt::AlignRight);//从右侧显示
  setWindowTitle(QString("简易计算器"));//设置标题
  QAction* mortgage = new QAction("利息计算器");
  QToolBar* tool = new QToolBar(this);
  tool->addAction(mortgage);

  connect(mortgage, &QAction::triggered, this, [=](){
    Mortgage* m = new Mortgage();
    m->show();
    ;});
  connects();
}

Widget::~Widget()
{
  delete ui;
}

bool check(QCharRef c){
  return (c >= '0' && c <= '9');
}
//用中缀表达式计算
void Widget::getInfix(){
  for(int i = 0; i < in.size(); i++){
    QString num, op;
    bool ok = false;
    while((in[i] >= '0' && in[i] <= '9') || in[i] == '.'){
      num.push_back(in[i]);
      ok = true;
      i++;
    }
    if(ok) out.push_back(num);
    if(in[i] != '\0'){
      //对于是负数的情况的处理方式
      QString res;
      if(in[i] == '-' && (i == 0 ||check(in[i-1]) == 0)){
        int pos = i+1;
        res.push_back('-');
        while((in[pos] >= '0'  && in[i] <= '9' && in[i] != '^') || in[i] == '.' ){
          qDebug() << in[pos];
          res.push_back(in[pos]);
          pos++;
        }
        out.push_back(res);
        i = pos-1;
        qDebug() << i;
        continue;
      }
      //cos c sin s sqrt q
      op = in[i];
      out.push_back(op);
    }
  }
  for(int i = 0; i < out.size(); i++){
    qDebug() << out[i];
  }
}

const char pri[9][9] = {
  // 当前的操作符
          // +    -    *    /    ^    !    (    )   \0
  /*   + */ '>', '>', '<', '<', '<', '<', '<', '>', '>',
  /*   - */ '>', '>', '<', '<', '<', '<', '<', '>', '>',
  /*   * */ '>', '>', '>', '>', '<', '<', '<', '>', '>',
  /*   / */ '>', '>', '<', '<', '<', '<', '<', '>', '>',
  /*   ^ */ '>', '>', '>', '>', '>', '<', '<', '>', '>',
  /*   ! */ '>', '>', '>', '>', '>', '>', ' ', '>', '>',
  /*   ( */ '<', '<', '<', '<', '<', '<', '<', '=', ' ',
  /*   ) */ ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
  /*  \0 */ '<', '<', '<', '<', '<', '<', '<', ' ', '='
};

int getNum(char a){
  if(a == '+') return 0;
  if(a == '-') return 1;
  if(a == '*') return 2;
  if(a == '/') return 3;
  if(a == '^') return 4;
  if(a == '!') return 5;
  if(a == '(') return 6;
  if(a == ')') return 7;
  if(a == '\0')return 8;
}

char orderBetween(char x, char y){
  int nx = getNum(x);
  int ny = getNum(y);
  return pri[nx][ny];
}

double cal(double a, char op, double b){
  if(op == '+')return a+b;
  if(op == '-')return a-b;
  if(op == '*')return a*b;
  if(op == '/')return a/b;
  if(op == '^')return pow(a, b);
}

bool expressionError = false;

void Widget::calInfix(){
  QStack<double> num; QStack<char> optr;
  optr.push('\0');
  int pos = 0;
  //qDebug() << out.size();
  while(!optr.empty()){
    //qDebug() << " asdasd " <<optr.top();
    bool is_num = false;
    if(pos < out.size())out[pos].toDouble(&is_num);
    char op;
    if(pos == out.size())op = '\0';
    if(!is_num && pos < out.size()) op = out[pos].at(0).unicode(); // QString数据类型转char类型
    if(is_num){
      double number = out[pos].toDouble();
      num.push_back(number);
      pos++;
    }
    else switch (orderBetween(optr.top(), op)) {
      case '<':
        { optr.push(op); pos++; break;}
      case '=':
        {optr.pop(); pos++; break;}
      case '>':{
        char _op = optr.pop();
        if(num.empty()){
          expressionError = true;
          return;
        }
        double opNum2 = num.pop();
        if(num.empty()){
          expressionError = true;
          return;
        }
        double opNum1 = num.pop();
        num.push(cal(opNum1, _op, opNum2));
      }
    }
    //qDebug() << num.top() << " op: " << op << " opsize " << optr.size();
  }
  if(!num.empty())result = num.top();
  else result = 0;
}

void Widget::init(){
  in.clear();
  out.clear();
}

void Widget ::pushButton0_clicked(){
  QString str = ui->lineEdit->text();
  ui->lineEdit->setText(QString("%1%2").arg(str).arg(0));
}
void Widget ::pushButton1_clicked(){
  QString str = ui->lineEdit->text();
  ui->lineEdit->setText(QString("%1%2").arg(str).arg(1));
}
void Widget ::pushButton2_clicked(){
  QString str = ui->lineEdit->text();
  ui->lineEdit->setText(QString("%1%2").arg(str).arg(2));
}
void Widget ::pushButton3_clicked(){
  QString str = ui->lineEdit->text();
  ui->lineEdit->setText(QString("%1%2").arg(str).arg(3));
}
void Widget ::pushButton4_clicked(){
  QString str = ui->lineEdit->text();
  ui->lineEdit->setText(QString("%1%2").arg(str).arg(4));
}
void Widget ::pushButton5_clicked(){
  QString str = ui->lineEdit->text();
  ui->lineEdit->setText(QString("%1%2").arg(str).arg(5));
}
void Widget ::pushButton6_clicked(){
  QString str = ui->lineEdit->text();
  ui->lineEdit->setText(QString("%1%2").arg(str).arg(6));
}
void Widget ::pushButton7_clicked(){
  QString str = ui->lineEdit->text();
  ui->lineEdit->setText(QString("%1%2").arg(str).arg(7));
}
void Widget ::pushButton8_clicked(){
  QString str = ui->lineEdit->text();
  ui->lineEdit->setText(QString("%1%2").arg(str).arg(8));
}
void Widget ::pushButton9_clicked(){
  QString str = ui->lineEdit->text();
  ui->lineEdit->setText(QString("%1%2").arg(str).arg(9));
}
void Widget ::pushButton_add_clicked(){
  QString str = ui->lineEdit->text();
  ui->lineEdit->setText(QString("%1%2").arg(str).arg("+"));
}
void Widget ::pushButton_minus_clicked(){
  QString str = ui->lineEdit->text();
  ui->lineEdit->setText(QString("%1%2").arg(str).arg("-"));
}
void Widget ::pushButton_mul_clicked(){
  QString str = ui->lineEdit->text();
  ui->lineEdit->setText(QString("%1%2").arg(str).arg("*"));
}
void Widget ::pushButton_div_clicked(){
  QString str = ui->lineEdit->text();
  ui->lineEdit->setText(QString("%1%2").arg(str).arg("/"));
}
void Widget :: pushButton_pow_clicked(){
  QString str = ui->lineEdit->text();
  ui->lineEdit->setText(QString("%1%2").arg(str).arg("^"));
}
void Widget ::pushButton_left_clicked(){
  QString str = ui->lineEdit->text();
  ui->lineEdit->setText(QString("%1%2").arg(str).arg("("));
}
void Widget ::pushButton_right_clicked(){
  QString str = ui->lineEdit->text();
  ui->lineEdit->setText(QString("%1%2").arg(str).arg(")"));
}
void Widget ::pushButton_point_clicked(){
  QString str = ui->lineEdit->text();
  ui->lineEdit->setText(QString("%1%2").arg(str).arg("."));
}
void Widget ::pushButton_equal_clicked(){
  in = ui->lineEdit->text();
  getInfix();
    calInfix();
    ui->lineEdit->clear();
    if(!expressionError)ui->lineEdit->setText(QString("%1").arg(result));
    else ui->lineEdit->setText("expression error");
}
void Widget ::pushButton_delete_clicked(){
  ui->lineEdit->clear();
  init();
}
void Widget ::pushButton_backspace_clicked(){
  ui->lineEdit->backspace();
}
void Widget :: connects(){
  connect(ui->pushButton_1, &QPushButton::clicked, this, &Widget::pushButton1_clicked);
  connect(ui->pushButton_2, &QPushButton::clicked, this, &Widget::pushButton2_clicked);
  connect(ui->pushButton_3, &QPushButton::clicked, this, &Widget::pushButton3_clicked);
  connect(ui->pushButton_4, &QPushButton::clicked, this, &Widget::pushButton4_clicked);
  connect(ui->pushButton_5, &QPushButton::clicked, this, &Widget::pushButton5_clicked);
  connect(ui->pushButton_6, &QPushButton::clicked, this, &Widget::pushButton6_clicked);
  connect(ui->pushButton_7, &QPushButton::clicked, this, &Widget::pushButton7_clicked);
  connect(ui->pushButton_8, &QPushButton::clicked, this, &Widget::pushButton8_clicked);
  connect(ui->pushButton_9, &QPushButton::clicked, this, &Widget::pushButton9_clicked);
  connect(ui->pushButton_0, &QPushButton::clicked, this, &Widget::pushButton0_clicked);
  connect(ui->pushButton_point, &QPushButton::clicked, this, &Widget::pushButton_point_clicked);

  connect(ui->pushButton_add, &QPushButton::clicked, this, &Widget::pushButton_add_clicked);
  connect(ui->pushButton_minus, &QPushButton::clicked, this, &Widget::pushButton_minus_clicked);
  connect(ui->pushButton_mul, &QPushButton::clicked, this, &Widget::pushButton_mul_clicked);
  connect(ui->pushButton_div, &QPushButton::clicked, this, &Widget::pushButton_div_clicked);
  connect(ui->pushButton_pow, &QPushButton::clicked, this, &Widget :: pushButton_pow_clicked);

  connect(ui->pushButton_left, &QPushButton::clicked, this, &Widget::pushButton_left_clicked);
  connect(ui->pushButton_right, &QPushButton::clicked, this, &Widget::pushButton_right_clicked);

  connect(ui->pushButton_delete, &QPushButton::clicked, this, &Widget::pushButton_delete_clicked);
  connect(ui->pushButton_backspace, &QPushButton::clicked, this, &Widget::pushButton_backspace_clicked);

  connect(ui->pushButton_equal, &QPushButton :: clicked, this, &Widget::pushButton_equal_clicked);
}
