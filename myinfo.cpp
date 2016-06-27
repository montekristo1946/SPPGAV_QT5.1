#include "myinfo.h"
#include "ui_myinfo.h"

MyInfo::MyInfo(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MyInfo)
{
    ui->setupUi(this);
    this->setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);//скрыть кнопку контекстной помощи
}

MyInfo::~MyInfo()
{
    //qDebug()<< "Разрушился MyInfo() ";
    delete ui;
}

void MyInfo::on_pushButton_clicked()
{
    this->deleteLater();
}

void MyInfo::closeEvent(QCloseEvent *event)
{
    this->deleteLater();
    event->ignore();
}
