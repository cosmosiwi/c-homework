#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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

private:
  Ui::MainWindow *ui;
  QString filename;
  QTextEdit *te;
  QVector<QTextEdit*> Te;
  QTabWidget *centralWin;
  void init();
  int file_count = 0;
};
#endif // MAINWINDOW_H
