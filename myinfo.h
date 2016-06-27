#ifndef MYINFO_H
#define MYINFO_H

#include <QDialog>
//#include <QDebug>
#include <QMouseEvent>

namespace Ui {
class MyInfo;
}

class MyInfo : public QDialog
{
    Q_OBJECT

public:
    explicit MyInfo(QWidget *parent = 0);
    ~MyInfo();

private slots:
    void on_pushButton_clicked();

private:
    Ui::MyInfo *ui;
    void closeEvent(QCloseEvent *event);
};

#endif // MYINFO_H
