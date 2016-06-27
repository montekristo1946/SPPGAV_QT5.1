#include "ping.h"
#include "ui_ping.h"

Ping::Ping(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Ping)
{
    ui->setupUi(this);



    ui->lineEdit_1->setText("192.168.1.201");//менюшку инициализируем
    ui->lineEdit_2->setText("80");
    this->setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);//скрыть кнопку контекстной помощи


}

Ping::~Ping()
{

    delete ui;
}
bool Ping::MYgetHostStatus(QString IP, QString port)
{

    socket = new QTcpSocket;

    socket->connectToHost(IP, port.toInt());
    if(socket->waitForConnected(1000))
    {
        //qDebug() << "true";
        socket->disconnectFromHost();
        return true;
    }
    else
    {
       // qDebug() << "false";
         return false;
    }



}

void Ping::on_pushButton_clicked()
{
    Ping h;
    ui->label_1->setText("");
    QPixmap PingTrue(20,20);
    // QPixmap PingTrue (":/img/videocamera_run.png");
    QSize Picsuze (20,20);



    if (h.MYgetHostStatus(ui->lineEdit_1->text(),
                          ui->lineEdit_2->text()))
    {
        PingTrue.load(":/img/videocamera_run.png");
        //   qDebug() <<"metka1";


    }
    else
    {
        PingTrue.load (":/img/videocamera_stop.png");


        //  qDebug() <<"metka2";
    }

    PingTrue = PingTrue.scaled(Picsuze,Qt::KeepAspectRatio);

    ui->label_1->setPixmap(PingTrue);

}

void Ping::on_pushButton_2_clicked()
{
    this->deleteLater();
}



void Ping::closeEvent(QCloseEvent *event)
{
    this->deleteLater();
    event->ignore();
}
