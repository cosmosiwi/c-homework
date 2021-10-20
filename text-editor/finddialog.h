#ifndef FINDDIALOG_H
#define FINDDIALOG_H

#include <QDialog>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <QHBoxLayout>


class FindDialog : public QDialog
{
    Q_OBJECT

public:
    explicit FindDialog(QWidget *parent = 0);
    ~FindDialog();
signals:
    void searchSignal(const QString str);
public slots:
    void search();
    void emitsearchSignal();

private:
    QLineEdit *lineedit;
};

#endif // FINDDIALOG_H


