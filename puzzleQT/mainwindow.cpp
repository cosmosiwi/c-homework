#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ui_level.h"
#include <QPushButton>
#include <QDebug>
#include <level.h>
#include <mylabel.h>
#include <success.h>
#include "QToolBar"

MainWindow::MainWindow(QWidget *parent)
  : QMainWindow(parent)
  , ui(new Ui::MainWindow)
{
  ui->setupUi(this);
  ui->spinBox->setRange(3, 10);
  playPicture[0] = QPixmap(":/new/prefix1/res/timg.jpg");
  playPicture[1] = QPixmap(":/new/prefix1/res/OIP-C (1).jpg");
  playPicture[2] = QPixmap(":/new/prefix1/res/OIP-C (2).jpg");
  playPicture[3] = QPixmap(":/new/prefix1/res/OIP-C (3).jpg");
  playPicture[4] = QPixmap(":/new/prefix1/res/OIP-C.jpg");

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
//这个函数是用来切割图片的
void MainWindow::showIcon(int level){
  playNum = (levelNum-3)%5;
  QPixmap pixmap(playPicture[playNum]);
  int width = ui->picture->width();
  int height = ui->picture->height();
  QPixmap fix = pixmap.scaled(width, height, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
  ui->picture->setPixmap(fix);

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
  //QLabel为父类实现的myLabel的lab对象
  for(int i = 0; i < level*level; i++){
    lab = new MyLabel(this);
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
    pTimer->start(1000);//点击 开始计时
  }
  if(clickFront == NONE){
    clickFront = idNum;
  }
  else {
    //判断clickFront与idNum的关系
    if(!(clickFront % levelNum  == idNum % levelNum || clickFront == idNum-1 || clickFront == idNum+1)){
      clickFront = NONE;
      return;
    }
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
  for(int i = 0; i < labList.size(); i++){
    lab = labList[i].first;
    delete lab;
  }
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
