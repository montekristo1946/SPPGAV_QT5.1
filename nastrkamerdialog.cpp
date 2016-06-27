#include "nastrkamerdialog.h"
#include "ui_nastrkamerdialog.h"

NastrKamerDialog::NastrKamerDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NastrKamerDialog)
{

    ui->setupUi(this);
    //ui->label->setAlignment(Qt::AlignCenter);
    //ui->label->setText("Видеопоток "+QString::number(ui->spinBox->value()));// красивое название...
    this->setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);//скрыть кнопку контекстной помощи


}

NastrKamerDialog::~NastrKamerDialog()
{
    delete ui;
}

void NastrKamerDialog::closeEvent(QCloseEvent *event)
{
   // qDebug()<<"крестик нажал";
    this->deleteLater();
    event->ignore();
}



void NastrKamerDialog::myShow(const QPixmap image)
{

image_1=image;
update();



//p.begin(ui->widget);
 //p.drawEllipse(10, 10, 70, 100);
// p.end();

    /*
    QImage image_2;
    image_2 = image;
    QApplication::processEvents();
   // ui->label->setPixmap(QPixmap::fromImage(image));
    ui->label->setAlignment(Qt::AlignCenter);
    ui->label->setPixmap(QPixmap::fromImage(image_2).scaled(ui->label->size(),
                                                         Qt::KeepAspectRatio, Qt::FastTransformation));
    */
}

void NastrKamerDialog::on_pushButton_clicked()//старт видео
{
    //ui->label->clear();
    //ui->label->setText("Видеопоток "+QString::number(ui->spinBox->value()));

    emit SignalStartVideoViewer(QString::number(ui->spinBox->value())+"1");

    ui->spinBox->setEnabled(false);//выключить кнопу
    ui->pushButton->setEnabled(false);//выключить кнопу
}


void NastrKamerDialog::on_pushButton_2_clicked()//стоп видео
{

    emit SignalStartVideoViewer(QString::number(ui->spinBox->value())+"0");
    QApplication::processEvents();//чеб не зависала вся программа
   // ui->label->clear();
    //ui->label->setText("Видеопоток "+QString::number(ui->spinBox->value()));
    ui->spinBox->setEnabled(true);//включить кнопу
    ui->pushButton->setEnabled(true);//включить кнопу


image_1.fill();//залить белым цветом...
   update();

}

void NastrKamerDialog::on_pushButton_3_clicked()
{
    this->deleteLater();
}

void NastrKamerDialog::paintEvent(QPaintEvent *event)
{
    QPainter painter( this );
   // painter.setPen( QPen( Qt::black, 3 ) );
   // painter.drawPoint( QPoint( x, y ) );
    painter.drawPixmap(10,50,this->geometry().width()-20,this->geometry().height()-55,image_1);

    // int tmp = this->geometry().height();
    //          this->geometry().width();
}
