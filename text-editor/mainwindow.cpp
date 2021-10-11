#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QPushButton"
#include "QStatusBar"
#include "QLabel"
#include "QTextEdit"
#include "QToolBar"
#include "QDockWidget"
#include "QDialog"
#include "iostream"
#include "QFileDialog"
#include "QDebug"
#include <QMessageBox>
#include <QColorDialog>
#include <QFontDialog>


MainWindow::MainWindow(QWidget *parent)
  : QMainWindow(parent)
  , ui(new Ui::MainWindow)
{
  ui->setupUi(this);
  //设置标题栏
  this->resize(900, 700);
  this->setWindowTitle("文本编辑器");
  this->setWindowIcon(QIcon(":/new/prefix1/files.png"));

  //设置菜单栏
  QMenu *file_menu = menuBar()->addMenu("文件");
  QMenu *file_edit = menuBar()->addMenu("编辑");

  //设置文件的选项
  QAction *file_new = new QAction(QIcon(":/new/prefix1/new-file.png"), "新建");
  QAction *file_open = new QAction(QIcon(":/new/prefix1/open-file.png"), "打开");
  QAction *file_saveas = new QAction(QIcon(":/new/prefix1/save-file.png"), "另存为");
  QAction *file_close = new QAction("关闭");
  file_menu->addAction(file_new);
  file_menu->addAction(file_open);
  file_menu->addAction(file_saveas);
  file_menu->addAction(file_close);

  QAction *edit_setfont = new QAction(QIcon(":/new/prefix1/font.png"), "字体设置");
  QAction *edit_setcolor = new QAction(QIcon(":/new/prefix1/color-palette.png"), "颜色设置");
  QAction *edit_copy = new QAction(QIcon(":/new/prefix1/files.png"), "复制");
  QAction *edit_paste = new QAction(QIcon(":/new/prefix1/paste.png"), "粘贴");
  QAction *edit_setBold = new QAction(QIcon(":/new/prefix1/bold.png"), "加粗");
  QAction *edit_setItalic = new QAction(QIcon(":/new/prefix1/italic.png"), "斜体");
  QAction *edit_setUnderline = new QAction(QIcon(":/new/prefix1/underline.png"), "下划线");

  file_edit->addAction(edit_setfont);//字体设置
  file_edit->addAction(edit_setcolor);//颜色设置
  file_edit->addAction(edit_copy);//复制
  file_edit->addAction(edit_paste);//粘贴
  //设置工具栏
  QToolBar *tb = addToolBar("工具");
  tb->addAction(file_new);
  tb->addAction(file_open);
  tb->addAction(file_saveas);

  tb->addAction(edit_setfont);
  tb->addAction(edit_setcolor);
  tb->addAction(edit_setBold);
  tb->addAction(edit_setItalic);
  tb->addAction(edit_setUnderline);
  tb->addAction(edit_copy);
  tb->addAction(edit_paste);

  //设置文本区
  centralWin = new QTabWidget();
  centralWin->setTabsClosable(true);
  this->setCentralWidget(centralWin);
  connect(centralWin, &QTabWidget::tabCloseRequested, this, [=](){fileClose();});

  //设置槽函数的链接
  connect(file_new, &QAction::triggered, this, [=](){fileNew();});
  connect(file_open, &QAction::triggered, this, [=](){fileOpen();});
  connect(file_saveas, &QAction::triggered, this, [=](){fileSaveas();});
  connect(file_close, &QAction::triggered, this, [=](){fileClose();});
  connect(edit_setfont, &QAction::triggered, this, [=](){editFont();});
  connect(edit_setcolor, &QAction::triggered, this, [=](){editColor();});
  connect(edit_copy, &QAction::triggered, this, [=](){editCopy();});
  connect(edit_paste, &QAction::triggered, this, [=](){editPaste();});
  connect(edit_setBold, &QAction::triggered, this, [=](){editBold();});
  connect(edit_setItalic, &QAction::triggered, this, [=](){editItalic();});
  connect(edit_setUnderline, &QAction::triggered, this, [=](){
    if(Te.size() == 0)return;
    te->setFontUnderline(true);
  });
}

void MainWindow::fileNew(){
  te = new QTextEdit;
  Te.push_back(te);
  char charNum = Te.size()+'0';
  char *x = &charNum;
  std::string stringNum = x;
  centralWin->addTab(te, QString::fromStdString("新建文档"+stringNum));

}

void MainWindow::fileOpen(){
  te = new QTextEdit;
  Te.push_back(te);
  filename = QFileDialog::getOpenFileName(this,"打开文件","C:/","*.txt *.c *.cpp *.h");
  if(filename=="")
      return;
  if(filename.right(3)=="txt"||filename.right(3)=="cpp"||filename.right(1)=="h"||filename.right(1)=="c"){
     QFile file(filename);
     if(file.open(QIODevice::ReadWrite)){
         QTextStream stream(&file);
         QString buf = stream.readAll();
         te->setText(buf);
         centralWin->addTab(te, filename);
     }
     file.close();
  }
  else
      QMessageBox::warning(this,"警告","不支持该格式的文件");
}

void MainWindow::fileSaveas(){
  if(Te.size() == 0)return;
  QFileInfo info(filename);
  if(info.exists()){
    QFile file(filename);
    if(file.open(QIODevice::WriteOnly)){
        QString buf = te->toPlainText();
        QTextStream stream(&file);
        stream<<buf;
        file.close();
    }
    return;
  }
  filename = QFileDialog::getSaveFileName(this,"另存为","C:", "Text file(*.txt/*.c/*.cpp/*.h)");
  if(filename=="")
      return;
  QFile file(filename);
  if(file.open(QIODevice::WriteOnly))
  {
      QTextStream stream(&file);
      QString buf = te->toPlainText();
      stream<<buf;
      file.close();
  }
}

int MainWindow::fileClose(){
    int idx = centralWin->currentIndex();
    centralWin->removeTab(idx);
    te = Te[idx];
    qDebug() << idx;
    te->clear();
    te->close();
    Te.remove(idx);
}

void MainWindow::editColor(){
  //if(Te.size() == 0)return;
  te->setTextColor(QColorDialog::getColor());
}

void MainWindow::editFont(){
  bool ok;
  //if(Te.size() == 0)return;
  te->setCurrentFont(QFontDialog::getFont(&ok));
}

void MainWindow::editCopy(){
  //if(Te.size() == 0)return;
  te->copy();
}

void MainWindow::editPaste(){
  //if(Te.size() == 0)return;
  te->paste();
}

void MainWindow::editBold(){
  //if(Te.size() == 0)return;
  //QFont font ( "Microsoft YaHei", 10, 75);
  te->setFontWeight(75);
}

void MainWindow::editItalic(){
  //if(Te.size() == 0)return;
  te->setFontItalic(true);
}

MainWindow::~MainWindow()
{
  delete ui;
}

void MainWindow::on_tabWidget_tabCloseRequested(int index)
{
    fileClose();
}
