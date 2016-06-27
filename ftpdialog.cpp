#include "ftpdialog.h"
#include "ui_ftpdialog.h"

FTPDialog::FTPDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FTPDialog)
{
    ui->setupUi(this);

    MyReadfile = new Readfile();

    ui->lineEdit->setText(MyReadfile->ReadSetting("Keyr04","1"));//FTP  -UrlFtp
    ui->lineEdit_2->setText(MyReadfile->ReadSetting("Keyw02","1"));//FTP логин -LoginFtp
    ui->lineEdit_3->setText(MyReadfile->ReadSetting("Keyq01","1"));//Парль -PasswordFtp
    ui->lineEdit_4->setText(MyReadfile->ReadSetting("Keye03","1"));//порт -Port

    if (MyReadfile->ReadSetting("Keyt23","1") == "on")//FTP отправка отчета на фТП
        ui->radioButton->setChecked(true);
    else ui->radioButton->setChecked(false);
    this->setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);//скрыть кнопку контекстной помощи

}

FTPDialog::~FTPDialog()
{
    delete MyReadfile;
    delete ui;
}

void FTPDialog::on_pushButton_clicked()//сохранить
{

    MyReadfile->VriteSetting("Keyq01",ui->lineEdit_3->text(),"1"); //FTP Парль -PasswordFtp
    MyReadfile->VriteSetting("Keyw02",ui->lineEdit_2->text(),"1");         //FTP логин -LoginFtp
    MyReadfile->VriteSetting("Keye03",ui->lineEdit_4->text(),"1"); //FTP порт -Port
    MyReadfile->VriteSetting("Keyr04",ui->lineEdit->text(),"1"); //FTP  -UrlFtp

   if( ui->radioButton->isChecked())
    MyReadfile->       VriteSetting("Keyt23","on","1"); //FTP отправка отчета на фТП
   else MyReadfile->       VriteSetting("Keyt23","off","1"); //FTP отправка отчета на фТП

   //qDebug()<< "отработал";
}

void FTPDialog::on_pushButton_3_clicked()//тест отправки файла на ФТП
{

}



void FTPDialog::on_pushButton_2_clicked()
{
    this->deleteLater();
}

void FTPDialog::closeEvent(QCloseEvent *event)
{
    this->deleteLater();
    event->ignore();
}
