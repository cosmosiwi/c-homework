#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "finddialog.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
class QTextEdit;
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

friend FindDialog;

private slots:
  void fileNew();
  void fileOpen();
  void fileSaveas();
  int fileClose();

  void editColor();
  void editFont();

  void editCopy();
  void editPaste();
  void editBold();
  void editItalic();

  void on_tabWidget_tabCloseRequested(int index);
  void serchStr(const QString &str);

private:
  Ui::MainWindow *ui;
  QString filename;
  QTextEdit *te;
  QVector<QTextEdit*> Te;
  QTabWidget *centralWin;
  FindDialog *findDialog;

  void init();
  int file_count = 0;

  int clickCount1 = 0, clickCount2 = 0, clickCount3 = 0;
};
#endif // MAINWINDOW_H
