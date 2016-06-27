#ifndef FTPDIALOG_H
#define FTPDIALOG_H

#include <QDialog>
#include <QMouseEvent>
#include "readfile.h"
#include "ftp.h"

namespace Ui {
class FTPDialog;
}

class FTPDialog : public QDialog
{
    Q_OBJECT

public:
    explicit FTPDialog(QWidget *parent = 0);
    ~FTPDialog();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::FTPDialog *ui;
    Readfile * MyReadfile;
    void closeEvent(QCloseEvent *event);
};

#endif // FTPDIALOG_H
