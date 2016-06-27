#ifndef NASTRPARAMKAMDIALOG_H
#define NASTRPARAMKAMDIALOG_H

#include <QDialog>
#include "readfile.h"
#include <QMessageBox>
#include <QMouseEvent>
//#include <QPainter>

namespace Ui {
class NastrParamKamDialog;
}

class NastrParamKamDialog : public QDialog
{
    Q_OBJECT

public:
    explicit NastrParamKamDialog(QWidget *parent = 0);
    ~NastrParamKamDialog();

private slots:
    void on_pushButton_clicked();
    void SlotUpdateFrame(QString);

    void on_pushButton_4_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::NastrParamKamDialog *ui;
      Readfile * MyReadfile;
      QPixmap OnTrue;
      QSize Picsuze ;
      void closeEvent(QCloseEvent *event);
};

#endif // NASTRPARAMKAMDIALOG_H
