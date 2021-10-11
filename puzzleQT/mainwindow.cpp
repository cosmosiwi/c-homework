#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ui_level.h"
#include <QPushButton>
#include <QDebug>
#include <level.h>
#include <mylabel.h>
#include <success.h>

int num = 9*8*7*6*5*4*3*2*1;

MainWindow::MainWindow(QWidget *parent)
  : QMainWindow(parent)
  , ui(new Ui::MainWindow)
{
  ui->setupUi(this);
  ui->spinBox->setRange(3, 10);
  showIcon(3);
  init();
  connect(ui->reset, &QPushButton::clicked, this, [=](){resetLogic(levelNum);});
  connect(ui->difficulty, &QPushButton::clicked, this, [=](){selectLogic();});
}

void MainWindow::selectLogic(){
  levelNum = ui->spinBox->value();
  resetLogic(levelNum);
}

MainWindow::~MainWindow()
{
  delete ui;
}

void MainWindow::showIcon(int level){
  QPixmap pixmap(":/new/prefix1/res/timg.jpg");
  qDebug() << pixmap.width() << pixmap.height();
  int labelWidth = pixmap.width()/level;
  int labelHeight = pixmap.height()/level;
  QVector<int> order(level*level);
  in_ord.resize(level*level);
  //根据std里面的next_permutation实现随机数组
  for(int i = 0; i < level*level; i++)order[i] = i;
  //这里还需要改进
  std::random_shuffle(order.begin(), order.end());
  in_ord = order;
  // 显示图片
  for(int i = 0; i < level*level; i++){
    MyLabel* lab = new MyLabel(this);
    lab->resize(labelWidth, labelHeight);
    QPixmap cur = pixmap.copy(order[i]%level*labelWidth, order[i]/level*labelHeight, labelWidth, labelHeight);
    lab->move(i%level*labelWidth, i/level*labelHeight);
    lab->setPixmap(cur);
    labList.append(qMakePair(lab, cur));
    in_order.insert(lab, order[i]);
    lab->show();
    connect(lab, &MyLabel::clicked, this, [=](){labClickedLogic(i);});
  }
}

void MainWindow::labClickedLogic(int idNum){
  if(check())return;
  if(isClicked == false){
    isClicked = true;
    pTimer->start(1000);
  }
  if(clickFront == NONE){
    clickFront = idNum;
  }
  else{
    MyLabel *lab1 = labList.at(clickFront).first, *lab2 = labList.at(idNum).first;
    QPixmap cur1 = labList.at(clickFront).second, cur2 = labList.at(idNum).second;
    lab1->setPixmap(cur2);
    lab2->setPixmap(cur1);
    labList[clickFront].second = cur2;
    labList[idNum].second = cur1;
    clickFront = NONE;
    int num = in_order[lab1];
    in_order[lab1] = in_order[lab2];
    in_order[lab2] = num;
  }
  if(check()){
    pTimer->stop();
    s.show();
    return;
  }
}

void MainWindow::resetLogic(int level){
  labList.clear();
  isClicked = false;
  delete pTimer;
  init();
  showIcon(level);
}

void MainWindow::init(){
  ui->lcdNumber->display("00:00:00");
  isClicked = false;
  pTimer = new QTimer;
  baseTime = baseTime.currentTime();
  connect(pTimer, SIGNAL(timeout()), this, SLOT(updateTime()));
}

void MainWindow::updateTime(){
  QTime currTime = QTime::currentTime();
  int t = baseTime.secsTo(currTime);
  QTime showTime(0, 0, 0, 0);
  showTime = showTime.addSecs(t);
  timeStr = showTime.toString("hh:mm:ss");
  ui->lcdNumber->display(timeStr);
}

bool MainWindow::check(){
  for(int i = 0; i < labList.size(); i++){
    auto item = labList[i].first;
    qDebug() << in_order[item];
    if(in_order[item] != i)return false;
  }
  return true;
}
