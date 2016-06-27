#include "nastrparamkamdialog.h"
#include "ui_nastrparamkamdialog.h"

NastrParamKamDialog::NastrParamKamDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NastrParamKamDialog)
{
    ui->setupUi(this);
    this->setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);//скрыть кнопку контекстной помощи
    MyReadfile = new Readfile();
    connect(ui->spinBox,SIGNAL(valueChanged(QString)),this,SLOT(SlotUpdateFrame(QString)));

    //setValidator(new QRegExpValidator(QRegExp("^([1-9][0-9]*|0)(\\.|,)[0-9]{2}"), this));
    //ui->lineEdit_R1->setValidator(new QDoubleValidator(-999.0,999.0, 2, this));


    ui->label_31->setText("");

    ui->lineEdit_15->setValidator(new QRegExpValidator(QRegExp("[0-2][0-9]"), this));
    ui->lineEdit_16->setValidator(new QRegExpValidator(QRegExp("[0-6][0-9]"), this));

    ui->lineEdit_17->setValidator(new QRegExpValidator(QRegExp("[0-2][0-9]"), this));
    ui->lineEdit_18->setValidator(new QRegExpValidator(QRegExp("[0-6][0-9]"), this));

    ui->lineEdit_20->setValidator(new QRegExpValidator(QRegExp("[0-2][0-9]"), this));
    ui->lineEdit_21->setValidator(new QRegExpValidator(QRegExp("[0-6][0-9]"), this));

    ui->lineEdit_22->setValidator(new QRegExpValidator(QRegExp("[0-2][0-9]"), this));
    ui->lineEdit_23->setValidator(new QRegExpValidator(QRegExp("[0-6][0-9]"), this));

    ui->lineEdit_2->setValidator(new QRegExpValidator(QRegExp("[0-9][0-9][0-9][0-9][0-9][0-9][0-9]"), this));
    ui->lineEdit_3->setValidator(new QRegExpValidator(QRegExp("[0-9][0-9][0-9][0-9][0-9][0-9]"), this));
    ui->lineEdit_4->setValidator(new QRegExpValidator(QRegExp("[0-9][0-9][0-9][0-9][0-9][0-9]"), this));
    ui->lineEdit_5->setValidator(new QRegExpValidator(QRegExp("[0-9][0-9][0-9][0-9][0-9][0-9]"), this));
    ui->lineEdit_6->setValidator(new QRegExpValidator(QRegExp("[0-9][0-9][0-9][0-9][0-9][0-9]"), this));
    ui->lineEdit_7->setValidator(new QRegExpValidator(QRegExp("[0-9][0-9][0-9][0-9][0-9][0-9]"), this));
    ui->lineEdit_8->setValidator(new QRegExpValidator(QRegExp("[0-9][0-9][0-9][0-9][0-9][0-9]"), this));
    ui->lineEdit_9->setValidator(new QRegExpValidator(QRegExp("[0-9][0-9][0-9][0-9][0-9][0-9]"), this));
    ui->lineEdit_10->setValidator(new QRegExpValidator(QRegExp("[0-9][0-9][0-9][0-9][0-9][0-9]"), this));
    ui->lineEdit_11->setValidator(new QRegExpValidator(QRegExp("[0-9][0-9][0-9][0-9][0-9][0-9]"), this));
    ui->lineEdit_12->setValidator(new QRegExpValidator(QRegExp("[0-9][0-9][0-9][0-9][0-9][0-9]"), this));
    ui->lineEdit_13->setValidator(new QRegExpValidator(QRegExp("[0-9][0-9][0-9][0-9][0-9][0-9]"), this));
    ui->lineEdit_14->setValidator(new QRegExpValidator(QRegExp("[0-9][0-9][0-9][0-9][0-9][0-9]"), this));
    ui->lineEdit_19->setValidator(new QRegExpValidator(QRegExp("[0-9][0-9][0-9][0-9][0-9][0-9]"), this));

    ui->lineEdit_28->setValidator(new QRegExpValidator(QRegExp("[0-9][0-9][0-9][0-9]"), this));
    ui->lineEdit_29->setValidator(new QRegExpValidator(QRegExp("[0-9][0-9][0-9][0-9]"), this));

    //камеры
    ui->lineEdit_26->setText(MyReadfile->ReadSetting("Keyb22",ui->spinBox->text()));//Login Cam1
    ui->lineEdit_25->setText(MyReadfile->ReadSetting("Keyn31",ui->spinBox->text()));//Pass Cam1
    ui->lineEdit->setText(MyReadfile->ReadSetting("Keym32",ui->spinBox->text()));//IP Cam1
    ui->lineEdit_24->setText(MyReadfile->ReadSetting("Keyq33",ui->spinBox->text()));//Port Cam1
    ui->lineEdit_27->setText(MyReadfile->ReadSetting("Keyw34",ui->spinBox->text()));//url Cam1

   //параметры видео
    if (MyReadfile->ReadSetting("Keye35",ui->spinBox->text()) == "on")
            ui->radioButton->setChecked(true);
    else  ui->radioButton->setChecked(false);

    ui->lineEdit_28->setText(MyReadfile->ReadSetting("Keyr36",ui->spinBox->text()));//ширина видео
    ui->lineEdit_29->setText(MyReadfile->ReadSetting("Keyt37",ui->spinBox->text()));//Высота видео


    ui->lineEdit_2->setText(MyReadfile->ReadSetting("Keyy05",ui->spinBox->text()));//IDD (7 знаков)
    ui->lineEdit_3->setText(MyReadfile->ReadSetting("Keyu06",ui->spinBox->text()));//Время подсчета,  через равные интервлы времени записыва
    ui->lineEdit_4->setText(MyReadfile->ReadSetting("Keyi07",ui->spinBox->text()));//максимльный круг обнаружения -MaxKrug
    ui->lineEdit_5->setText(MyReadfile->ReadSetting("Keyo08",ui->spinBox->text()));//минимальный круг обнаружения -MinKrug
    ui->lineEdit_6->setText(MyReadfile->ReadSetting("Keyp09",ui->spinBox->text()));//Центральная линия пересечения -line1
    ui->lineEdit_7->setText(MyReadfile->ReadSetting("Keya10",ui->spinBox->text()));//Верхняя линия пересченеия  -line4
    ui->lineEdit_8->setText(MyReadfile->ReadSetting("Keys11",ui->spinBox->text()));//Нижняя линия пересечения  -line4
    ui->lineEdit_9->setText(MyReadfile->ReadSetting("Keyd12",ui->spinBox->text()));//Колличество кадров жизнь обьекта -Livepeople
    ui->lineEdit_10->setText(MyReadfile->ReadSetting("Keyf13",ui->spinBox->text()));//Порог перекрытия обьектов -PorogPerekritiy
    ui->lineEdit_11->setText(MyReadfile->ReadSetting("Keyg14",ui->spinBox->text()));//Круг человека -KrugCheloveka
    ui->lineEdit_12->setText(MyReadfile->ReadSetting("Keyh15",ui->spinBox->text()));//Фиксированое расстояние между обьектами которые движутся -RastoynieMegduChelami
    ui->lineEdit_13->setText(MyReadfile->ReadSetting("Keyj16",ui->spinBox->text()));//Порог Детекции между фоном и новой картинкой -porogSetup
    ui->lineEdit_14->setText(MyReadfile->ReadSetting("Keyk17",ui->spinBox->text()));//Кол Кадров,после которых обновится фон -BackgroundUpdate

    ui->lineEdit_19->setText(MyReadfile->ReadSetting("Keyl25",ui->spinBox->text()));//-Мгновенная контрасность InstantaneousContrast

    ui->lineEdit_15->setText(MyReadfile->ReadSetting("Keyz18",ui->spinBox->text()));//-timeONRunH
    ui->lineEdit_16->setText(MyReadfile->ReadSetting("Keyx19",ui->spinBox->text()));//-timeONRunM
    ui->lineEdit_17->setText(MyReadfile->ReadSetting("Keyc20",ui->spinBox->text()));//-timeOFFRunH
    ui->lineEdit_18->setText(MyReadfile->ReadSetting("Keyv21",ui->spinBox->text()));//-timeOFFRunM

    //запись видео
    ui->lineEdit_22->setText(MyReadfile->ReadSetting("Keyz27",ui->spinBox->text()));
    ui->lineEdit_23->setText(MyReadfile->ReadSetting("Keyx28",ui->spinBox->text()));
    ui->lineEdit_20->setText(MyReadfile->ReadSetting("Keyc29",ui->spinBox->text()));
    ui->lineEdit_21->setText(MyReadfile->ReadSetting("Keyv30",ui->spinBox->text()));



    if (MyReadfile->ReadSetting("Keym24",ui->spinBox->text())== "on")//Включена ли камера!
    {
        ui->pushButton_4->setEnabled(false);
        ui->pushButton_3->setEnabled(true);
        OnTrue.load(":/img/step_run_128x128.png");
    }
    else
    {
        ui->pushButton_3->setEnabled(false);
        ui->pushButton_4->setEnabled(true);
        OnTrue.load(":/img/step_stop_128x128.png");
    }


    if (MyReadfile->ReadSetting("Keyq26","1")== "on")
    {
        ui->pushButton_5->setEnabled(false);
        ui->pushButton_6->setEnabled(true);
    }
    else
    {
        ui->pushButton_6->setEnabled(false);
        ui->pushButton_5->setEnabled(true);
    }

    OnTrue = OnTrue.scaled(QSize(30,30),Qt::KeepAspectRatio);
    ui->label_31->setPixmap(OnTrue);

    /*
     *  VriteSetting("Key05","0001212",QString::number(i)); //IDD (7 знаков)
        VriteSetting("Key06","900",QString::number(i)); //Время подсчета,  через равные интервлы времени записываем в файл -inTimePodshet
        VriteSetting("Key07","15000",QString::number(i)); //максимльный круг обнаружения -MaxKrug
        VriteSetting("Key08","1000",QString::number(i)); //минимальный круг обнаружения -MinKrug
        VriteSetting("Key09","120",QString::number(i)); //Центральная линия пересечения -line1
        VriteSetting("Key10","40",QString::number(i)); //Верхняя линия пересченеия  -line4
        VriteSetting("Key11","200",QString::number(i)); //Нижняя линия пересечения  -line4
        VriteSetting("Key12","4",QString::number(i)); //Колличество кадров жизнь обьекта -Livepeople
        VriteSetting("Key13","10",QString::number(i)); //Порог перекрытия обьектов -PorogPerekritiy
        VriteSetting("Key14","50",QString::number(i)); //Круг человека -KrugCheloveka
        VriteSetting("Key15","70",QString::number(i)); //Фиксированое расстояние между обьектами которые движутся -RastoynieMegduChelami
        VriteSetting("Key16","140",QString::number(i)); //Порог Детекции между фоном и новой картинкой -porogSetup
        VriteSetting("Key17","500",QString::number(i)); //Кол Кадров,после которых обновится фон -BackgroundUpdate

        //включение и выключения подсчета по расписанию
        VriteSetting("Key18","10",QString::number(i)); //-timeONRunH
        VriteSetting("Key19","00",QString::number(i)); //-timeONRunM
        VriteSetting("Key20","22",QString::number(i)); //-timeOFFRunH
        VriteSetting("Key21","00",QString::number(i)); //-timeOFFRunM

        //камеры
        //VriteSetting("Key22","http://admin:admin@192.168.2.5/video/mjpg.cgi?.mjpg",QString::number(i)); //-Cam1
        VriteSetting("Key22","d:\\opencv\\5-2.avi",QString::number(i)); //-Cam1
        */
}

NastrParamKamDialog::~NastrParamKamDialog()
{
    delete MyReadfile;
    delete ui;

}

void NastrParamKamDialog::on_pushButton_clicked()//кнопа сохранения
{
    // MyReadfile->VriteSetting("Key22",ui->lineEdit->text(),"0");

    if ( ui->lineEdit_17->text().toInt()<ui->lineEdit_15->text().toInt())
    {

        QMessageBox::critical(NULL,QObject::tr("Ошибка"),
                              tr("Не соответствия начала и окончания работы СПП!"));
        return;
    }

    if ( ui->lineEdit_20->text().toInt()<ui->lineEdit_22->text().toInt())
    {

        QMessageBox::critical(NULL,QObject::tr("Ошибка"),
                              tr("Не соответствия начала и окончания записи видео"));
        return;
    }

    MyReadfile->VriteSetting("Keyb22",ui->lineEdit_26->text(),ui->spinBox->text());//Login Cam1
   MyReadfile->VriteSetting("Keyn31",ui->lineEdit_25->text(),ui->spinBox->text());//Pass Cam1
    MyReadfile->VriteSetting("Keym32",ui->lineEdit->text(),ui->spinBox->text());//IP Cam1
    MyReadfile->VriteSetting("Keyq33",ui->lineEdit_24->text(),ui->spinBox->text());//Port Cam1
    MyReadfile->VriteSetting("Keyw34",ui->lineEdit_27->text(),ui->spinBox->text());//url Cam1

    //параметры видео

    MyReadfile->VriteSetting("Keyr36",ui->lineEdit_28->text(),ui->spinBox->text());
    MyReadfile->VriteSetting("Keyt37",ui->lineEdit_29->text(),ui->spinBox->text());

    if (ui->radioButton->isChecked())
        MyReadfile->VriteSetting("Keye35","on",ui->spinBox->text());
    else MyReadfile->VriteSetting("Keye35","off",ui->spinBox->text());


    MyReadfile->VriteSetting("Keyy05",ui->lineEdit_2->text(),ui->spinBox->text());//IDD (7 знаков)
    MyReadfile->VriteSetting("Keyu06",ui->lineEdit_3->text(),ui->spinBox->text());//Время подсчета,  через равные интервлы времени записыва
    MyReadfile->VriteSetting("Keyi07",ui->lineEdit_4->text(),ui->spinBox->text());//максимльный круг обнаружения -MaxKrug
    MyReadfile->VriteSetting("Keyo08",ui->lineEdit_5->text(),ui->spinBox->text());//минимальный круг обнаружения -MinKrug
    MyReadfile->VriteSetting("Keyp09",ui->lineEdit_6->text(),ui->spinBox->text());//Центральная линия пересечения -line1
    MyReadfile->VriteSetting("Keya10",ui->lineEdit_7->text(),ui->spinBox->text());//Верхняя линия пересченеия  -line4
    MyReadfile->VriteSetting("Keys11",ui->lineEdit_8->text(),ui->spinBox->text());//Нижняя линия пересечения  -line4
    MyReadfile->VriteSetting("Keyd12",ui->lineEdit_9->text(),ui->spinBox->text());//Колличество кадров жизнь обьекта -Livepeople
    MyReadfile->VriteSetting("Keyf13",ui->lineEdit_10->text(),ui->spinBox->text());//Порог перекрытия обьектов -PorogPerekritiy
    MyReadfile->VriteSetting("Keyg14",ui->lineEdit_11->text(),ui->spinBox->text());//Круг человека -KrugCheloveka
    MyReadfile->VriteSetting("Keyh15",ui->lineEdit_12->text(),ui->spinBox->text());//Фиксированое расстояние между обьектами которые движутся -RastoynieMegduChelami
    MyReadfile->VriteSetting("Keyj16",ui->lineEdit_13->text(),ui->spinBox->text());//Порог Детекции между фоном и новой картинкой -porogSetup
    MyReadfile->VriteSetting("Keyk17",ui->lineEdit_14->text(),ui->spinBox->text());//Кол Кадров,после которых обновится фон -BackgroundUpdate

    MyReadfile->VriteSetting("Keyz18",ui->lineEdit_15->text(),ui->spinBox->text());//-timeONRunH
    MyReadfile->VriteSetting("Keyx19",ui->lineEdit_16->text(),ui->spinBox->text());//-timeONRunM
    MyReadfile->VriteSetting("Keyc20",ui->lineEdit_17->text(),ui->spinBox->text());//-timeOFFRunH
    MyReadfile->VriteSetting("Keyv21",ui->lineEdit_18->text(),ui->spinBox->text());//-timeOFFRunM

    MyReadfile->VriteSetting("Keyl25",ui->lineEdit_19->text(),ui->spinBox->text());//-Мгновенная контрасность InstantaneousContrast


    //запись видео
    MyReadfile->VriteSetting("Keyz27",ui->lineEdit_22->text(),ui->spinBox->text());
    MyReadfile->VriteSetting("Keyx28",ui->lineEdit_23->text(),ui->spinBox->text());
    MyReadfile->VriteSetting("Keyc29",ui->lineEdit_20->text(),ui->spinBox->text());
    MyReadfile->VriteSetting("Keyv30",ui->lineEdit_21->text(),ui->spinBox->text());

    if (!ui->pushButton_5->isEnabled())//Включена ли камера!
    {
        MyReadfile->VriteSetting("Keyq26","on","1");//
    }
    else
    {
        MyReadfile->VriteSetting("Keyq26","off","1");//
    }


    if (!ui->pushButton_4->isEnabled())//Включена ли камера!
    {
        MyReadfile->VriteSetting("Keym24","on",ui->spinBox->text());//
    }
    else
    {
        MyReadfile->VriteSetting("Keym24","off",ui->spinBox->text());//
    }

    QMessageBox::information(NULL,QObject::tr("Информация"),
                             tr("Для применения настроек перезагрузи приложение"));


}
void NastrParamKamDialog::SlotUpdateFrame(QString )
{
    //qDebug()<<tmp;
    ui->lineEdit_26->setText(MyReadfile->ReadSetting("Keyb22",ui->spinBox->text()));//Login Cam1
    ui->lineEdit_25->setText(MyReadfile->ReadSetting("Keyn31",ui->spinBox->text()));//Pass Cam1
    ui->lineEdit->   setText(MyReadfile->ReadSetting("Keym32",ui->spinBox->text()));//IP Cam1
    ui->lineEdit_24->setText(MyReadfile->ReadSetting("Keyq33",ui->spinBox->text()));//Port Cam1
    ui->lineEdit_27->setText(MyReadfile->ReadSetting("Keyw34",ui->spinBox->text()));//url Cam1



    if (ui->spinBox->text()=="1")//отключить если не в главном меню
    {
        ui->lineEdit_2->setEnabled(true);
        ui->lineEdit_2->setText(MyReadfile->ReadSetting("Keyy05","1"));//IDD (7 знаков)

        ui->lineEdit_15->setEnabled(true);
        ui->lineEdit_15->setText(MyReadfile->ReadSetting("Keyz18","1"));//-timeONRunH
        ui->lineEdit_16->setEnabled(true);
        ui->lineEdit_16->setText(MyReadfile->ReadSetting("Keyx19","1"));//-timeONRunM
        ui->lineEdit_17->setEnabled(true);
        ui->lineEdit_17->setText(MyReadfile->ReadSetting("Keyc20","1"));//-timeOFFRunH
        ui->lineEdit_18->setEnabled(true);
        ui->lineEdit_18->setText(MyReadfile->ReadSetting("Keyv21","1"));//-timeOFFRunM

        ui->lineEdit_22->setEnabled(true);
        ui->lineEdit_22->setText(MyReadfile->ReadSetting("Keyz27","1"));
        ui->lineEdit_23->setEnabled(true);
        ui->lineEdit_23->setText(MyReadfile->ReadSetting("Keyx28","1"));
        ui->lineEdit_20->setEnabled(true);
        ui->lineEdit_20->setText(MyReadfile->ReadSetting("Keyc29","1"));
        ui->lineEdit_21->setEnabled(true);
        ui->lineEdit_21->setText(MyReadfile->ReadSetting("Keyv30","1"));

        //параметры видео
        ui->radioButton->setEnabled(true);
         if (MyReadfile->ReadSetting("Keye35",ui->spinBox->text()) == "on")
                 ui->radioButton->setChecked(true);
         else  ui->radioButton->setChecked(false);

         ui->lineEdit_28->setEnabled(true);
         ui->lineEdit_29->setEnabled(true);
         ui->lineEdit_28->setText(MyReadfile->ReadSetting("Keyr36",ui->spinBox->text()));//ширина видео
         ui->lineEdit_29->setText(MyReadfile->ReadSetting("Keyt37",ui->spinBox->text()));//Высота видео

         ui->lineEdit_3->setEnabled(true);
         ui->lineEdit_3->setText(MyReadfile->ReadSetting("Keyu06",ui->spinBox->text()));//Время подсчета,  через равные интервлы времени записыва



        if (MyReadfile->ReadSetting("Keyq26","1")== "on")
        {
            ui->pushButton_5->setEnabled(false);
            ui->pushButton_6->setEnabled(true);
        }
        else
        {
            ui->pushButton_6->setEnabled(false);
            ui->pushButton_5->setEnabled(true);
        }

    }
    else
    {
        ui->lineEdit_3->setEnabled(false);
        ui->radioButton->setEnabled(false);
        ui->lineEdit_28->setEnabled(false);
        ui->lineEdit_29->setEnabled(false);

        ui->lineEdit_2->setEnabled(false);
        ui->lineEdit_15->setEnabled(false);
        ui->lineEdit_16->setEnabled(false);
        ui->lineEdit_17->setEnabled(false);
        ui->lineEdit_18->setEnabled(false);

        ui->lineEdit_22->setEnabled(false);
        ui->lineEdit_23->setEnabled(false);
        ui->lineEdit_20->setEnabled(false);
        ui->lineEdit_21->setEnabled(false);
        ui->pushButton_5->setEnabled(false);
        ui->pushButton_6->setEnabled(false);


    }

    ui->lineEdit_4->setText(MyReadfile->ReadSetting("Keyi07",ui->spinBox->text()));//максимльный круг обнаружения -MaxKrug
    ui->lineEdit_5->setText(MyReadfile->ReadSetting("Keyo08",ui->spinBox->text()));//минимальный круг обнаружения -MinKrug
    ui->lineEdit_6->setText(MyReadfile->ReadSetting("Keyp09",ui->spinBox->text()));//Центральная линия пересечения -line1
    ui->lineEdit_7->setText(MyReadfile->ReadSetting("Keya10",ui->spinBox->text()));//Верхняя линия пересченеия  -line4
    ui->lineEdit_8->setText(MyReadfile->ReadSetting("Keys11",ui->spinBox->text()));//Нижняя линия пересечения  -line4
    ui->lineEdit_9->setText(MyReadfile->ReadSetting("Keyd12",ui->spinBox->text()));//Колличество кадров жизнь обьекта -Livepeople
    ui->lineEdit_10->setText(MyReadfile->ReadSetting("Keyf13",ui->spinBox->text()));//Порог перекрытия обьектов -PorogPerekritiy
    ui->lineEdit_11->setText(MyReadfile->ReadSetting("Keyg14",ui->spinBox->text()));//Круг человека -KrugCheloveka
    ui->lineEdit_12->setText(MyReadfile->ReadSetting("Keyh15",ui->spinBox->text()));//Фиксированое расстояние между обьектами которые движутся -RastoynieMegduChelami
    ui->lineEdit_13->setText(MyReadfile->ReadSetting("Keyj16",ui->spinBox->text()));//Порог Детекции между фоном и новой картинкой -porogSetup
    ui->lineEdit_14->setText(MyReadfile->ReadSetting("Keyk17",ui->spinBox->text()));//Кол Кадров,после которых обновится фон -BackgroundUpdate



    ui->lineEdit_19->setText(MyReadfile->ReadSetting("Keyl25",ui->spinBox->text()));//-Мгновенная контрасность InstantaneousContrast



    if (MyReadfile->ReadSetting("Keym24",ui->spinBox->text())== "on")//Включена ли камера!
    {
        ui->pushButton_4->setEnabled(false);
        ui->pushButton_3->setEnabled(true);
        OnTrue.load(":/img/step_run_128x128.png");
    }
    else
    {
        ui->pushButton_3->setEnabled(false);
        ui->pushButton_4->setEnabled(true);
        OnTrue.load(":/img/step_stop_128x128.png");
    }

    OnTrue = OnTrue.scaled(QSize(30,30),Qt::KeepAspectRatio);
    ui->label_31->setPixmap(OnTrue);

}




void NastrParamKamDialog::on_pushButton_4_clicked()//on
{
    ui->pushButton_4->setEnabled(false);
    ui->pushButton_3->setEnabled(true);
    OnTrue.load(":/img/step_run_128x128.png");
    OnTrue = OnTrue.scaled(QSize(30,30),Qt::KeepAspectRatio);
    ui->label_31->setPixmap(OnTrue);
}

void NastrParamKamDialog::on_pushButton_3_clicked()//off
{
    ui->pushButton_3->setEnabled(false);
    ui->pushButton_4->setEnabled(true);
    OnTrue.load(":/img/step_stop_128x128.png");
    OnTrue = OnTrue.scaled(QSize(30,30),Qt::KeepAspectRatio);
    ui->label_31->setPixmap(OnTrue);
}

void NastrParamKamDialog::on_pushButton_5_clicked()//on запись потока
{   ui->pushButton_5->setEnabled(false);
    ui->pushButton_6->setEnabled(true);

}

void NastrParamKamDialog::on_pushButton_6_clicked()//off запись потока
{
    ui->pushButton_6->setEnabled(false);
    ui->pushButton_5->setEnabled(true);
}

void NastrParamKamDialog::on_pushButton_2_clicked()
{
    this->deleteLater();
}

void NastrParamKamDialog::closeEvent(QCloseEvent *event)
{
    this->deleteLater();
    event->ignore();
}
