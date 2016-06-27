#ifndef NASTRKAMERDIALOG_H
#define NASTRKAMERDIALOG_H

#include <QDialog>
#include <QMessageBox>

#include <QMainWindow>
#include <QSystemTrayIcon>
#include <QTime>
#include <QMouseEvent>
#include <QPainter>



#include "myvideothread.h"

namespace Ui {
class NastrKamerDialog;
}

class NastrKamerDialog : public QDialog
{
    Q_OBJECT

public:
    explicit NastrKamerDialog(QWidget *parent = 0);
    ~NastrKamerDialog();
    QPainter p;

private:
    Ui::NastrKamerDialog *ui;
    MyVideoThread * VideoPotok1;

   void closeEvent(QCloseEvent *event);
   //int x;
   //int y;
   QPixmap image_1;



private slots:
    void myShow(const QPixmap image);
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

signals:
    void SignalStartVideoViewer(QString);
    //void SignalStopVideoViewer(QString);

protected:
    void paintEvent(QPaintEvent *event );


};

#endif // NASTRKAMERDIALOG_H







