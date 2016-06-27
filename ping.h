#ifndef PING_H
#define PING_H

#include <QDialog>
#include <QTcpSocket>
#include <QMouseEvent>
#include <QTimer>

namespace Ui {
class Ping;
}

class Ping : public QDialog
{
    Q_OBJECT

public:
    explicit Ping(QWidget *parent = 0);
    ~Ping();

    bool MYgetHostStatus(QString IP, QString port);

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();



private:
    Ui::Ping *ui;
    QTcpSocket *socket;
    void closeEvent(QCloseEvent *event);

};

#endif // PING_H
