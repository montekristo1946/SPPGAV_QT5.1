#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <stdio.h>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui -> setupUi(this);
    this -> setTrayIconActions();
    this -> showTrayIcon();
    emit LisCensiy();


    MyReadfile = new Readfile();//клас для записи и чтения файлов
    connect(MyReadfile,SIGNAL(SignalLogView(QString)),this,SLOT(SlotLogView(QString)));


    VideoPotok1 = new MyVideoThread(0,1);
    VideoPotok2 = new MyVideoThread(0,2);
    VideoPotok3 = new MyVideoThread(0,3);
    VideoPotok4 = new MyVideoThread(0,4);
    VideoPotok5 = new MyVideoThread(0,5);
    VideoPotok6 = new MyVideoThread(0,6);

    TimeLogFtp = MyReadfile->ReadSetting("Keyu06","1");//переменная для вывода в логах!

    //if (TimeLogFtp==NULL )emit SlotLogView("Проблема с параметром Time Log Ftp");

    //активируем таймер ФТП
     timerFTP.start(TimeLogFtp.toInt()*1000);//15 минут (900000)
   // timerFTP.start(30000);
      connect(&timerFTP, SIGNAL(timeout()), this, SLOT(FTPAlarm()));

    //активируем таймер контроля потоков
    timerAlarm.start(120000);//2 минуты
    //timerAlarm.start(10000);
    connect(&timerAlarm, SIGNAL(timeout()), this, SLOT(StoragAlarm()));


    //активируем таймер обмне данными между потоками
    timerPerenosDanuPotokAlarm.start(60000);//1 минута
   // timerPerenosDanuPotokAlarm.start(6000);//1 минута
    connect(&timerPerenosDanuPotokAlarm, SIGNAL(timeout()), this, SLOT(SlotPerenosDanuPotokAlarm()));


    initPainter();//инициализация параметров


    QTimer * LisCensiyTimer;
     LisCensiyTimer= new QTimer();
     LisCensiyTimer->start(10800000);//3 часа
     connect(LisCensiyTimer, SIGNAL(timeout()), this, SLOT(LisCensiy()));




    ui->textEdit->document()->setMaximumBlockCount(1000);//задать количество строк!
    ui->textEdit->setReadOnly(true);//запретить редактировать

    //конектим вывод лога с класса ФТП
 //   myFtp = new Ftp();
 //   connect(myFtp,SIGNAL(SignalLogView(QString)),this,SLOT(SlotLogView(QString)));

}

MainWindow::~MainWindow()
{
timerFTPAll.deleteLater();
timerFTP.deleteLater();
timerAlarm.deleteLater();
timerPerenosDanuPotokAlarm.deleteLater();

    VideoPotok1->deleteLater();

     VideoPotok2->deleteLater();
     VideoPotok3->deleteLater();
     VideoPotok4->deleteLater();
     VideoPotok5->deleteLater();
     VideoPotok6->deleteLater();
     MyReadfile->deleteLater();
     if(MyNastrParamKamDialog)  MyNastrParamKamDialog->deleteLater();
     if(NastroykaKamerDialog)  NastroykaKamerDialog->deleteLater();
     if(ftpDialog)  ftpDialog->deleteLater();
     if(myPing)  myPing->deleteLater();

     // delete MyNastrParamKamDialog;
   //  qDebug()<<" разрушился MainWindow" ;

    //  delete NastroykaKamerDialog;
    // delete ftpDialog;
   // delete myPing;

    delete ui;

}

void MainWindow::SlotLogView(QString text)
{
    TimeLogNow = QTime::currentTime();//получаем текущее время системы
    DateLogNow = QDate::currentDate();
    ui->textEdit->moveCursor(QTextCursor::End);//устанавливаем последную строку курсора
    //должна получится строка вида "22:49:46 13.11.2014 Текст собщения"
    //toString("dd.MM.yyyy")+" "+TimeNow.toString("HH:mm:ss")
    /* ui->textEdit->insertPlainText(QString::number(TimeLogNow.hour())+":"+
                                  QString::number(TimeLogNow.minute())+":"+
                                  QString::number(TimeLogNow.second())+" "+
                                  QString::number(DateLogNow.day())+"."+
                                  QString::number(DateLogNow.month())+"."+
                                  QString::number(DateLogNow.year())+" "+
                                  text+"\n");*/
    ui->textEdit->insertPlainText(TimeLogNow.toString("HH:mm:ss")+"_"+DateLogNow.toString("dd.MM.yyyy")+" - "+text+"\n");


///////////////Отладка удали
//settings_1->setValue(TimeLogNow.toString("HH:mm:ss")+"_"+DateLogNow.toString("dd.MM.yyyy"),text);
 //   MyReadfile->WriteDebugLOG(TimeLogNow.toString("HH:mm:ss")+"_"+DateLogNow.toString("dd.MM.yyyy")+" - "+text+"\n");
///////////////Отладка удали

}

void MainWindow::showTrayIcon()
{
    // Создаём экземпляр класса и задаём его свойства...
    trayIcon = new QSystemTrayIcon(this);
    QIcon trayImage(":/img/step_png.png");
    trayIcon -> setIcon(trayImage);
    trayIcon -> setContextMenu(trayIconMenu);

    // Подключаем обработчик клика по иконке...
    connect(trayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)), this, SLOT(trayIconActivated(QSystemTrayIcon::ActivationReason)));

    // Выводим значок...
    trayIcon -> show();

}
void MainWindow::trayActionExecute()
{
    QMessageBox::information(this, "Сообщение", "Для корректной работы СПП - нельзя закрывать службу");
}

void MainWindow::trayIconActivated(QSystemTrayIcon::ActivationReason reason)
{
    switch (reason)
    {
    case QSystemTrayIcon::Trigger:
    case QSystemTrayIcon::DoubleClick:
        this -> trayActionExecute();
        break;
    default:
        break;
    }
}
void MainWindow::setTrayIconActions()
{
    // Setting actions...
    minimizeAction = new QAction("Свернуть", this);
    restoreAction = new QAction("Восстановить", this);
    quitAction = new QAction("Выход", this);

    // Connecting actions to slots...
    connect (minimizeAction, SIGNAL(triggered()), this, SLOT(hide()));
    connect (restoreAction, SIGNAL(triggered()), this, SLOT(showNormal()));
    connect (quitAction, SIGNAL(triggered()), qApp, SLOT(quit()));

    // Setting system tray's icon menu...
    trayIconMenu = new QMenu(this);
    trayIconMenu -> addAction (minimizeAction);
    trayIconMenu -> addAction (restoreAction);
    trayIconMenu -> addAction (quitAction);
}

void MainWindow::changeEvent(QEvent *event)
{
    QMainWindow::changeEvent(event);

    if (event -> type() == QEvent::WindowStateChange)
    {
        if (isMaximized())
        {
            this->show();
        }
    }
}

void MainWindow::on_action1_triggered()//Вывод Меню настройка камер
{
    // qDebug()<<"Меню настройка камер";
    NastroykaKamerDialog = new NastrKamerDialog();//диалоговое окно 2 настройка камер
    //подключил кнопки на форме "настройка Камер"
    connect(NastroykaKamerDialog,SIGNAL(SignalStartVideoViewer(QString)),this,SLOT(SlotConnektThreadVideo_1(QString)));

    NastroykaKamerDialog->show();

}
/*
void MainWindow::on_pushButton_clicked()//старт все потоки
{

}

void MainWindow::on_pushButton_2_clicked()//стоп все потоки
{


}*/


void MainWindow::SlotConnektThreadVideo_1(QString tmp)
{

    //первый поток
    if (tmp == "11"&&VideoPotok1&&VideoPotok1->StorogVideoPotok.OnPotok)
    {
        VideoPotok1->StorogVideoPotok.SendImege=true;
        connect(VideoPotok1, SIGNAL(MySendDataVideFrame(QPixmap)),NastroykaKamerDialog,SLOT(myShow(QPixmap)));//для отображения картинки

    }
    if (tmp == "10"&&VideoPotok1&&VideoPotok1->StorogVideoPotok.OnPotok)
    {
        VideoPotok1->StorogVideoPotok.SendImege=false;
        disconnect(VideoPotok1, SIGNAL(MySendDataVideFrame(QPixmap)),NastroykaKamerDialog,SLOT(myShow(QPixmap)));//для отображения картинки

    }

    //второй поток
    if (tmp == "21"&&VideoPotok2&&VideoPotok2->StorogVideoPotok.OnPotok)
    {
        VideoPotok2->StorogVideoPotok.SendImege=true;
        connect(VideoPotok2, SIGNAL(MySendDataVideFrame(QPixmap)),NastroykaKamerDialog,SLOT(myShow(QPixmap)));//для отображения картинки

    }
    if (tmp == "20"&&VideoPotok2&&VideoPotok2->StorogVideoPotok.OnPotok)
    {
        VideoPotok2->StorogVideoPotok.SendImege=false;
        disconnect(VideoPotok2, SIGNAL(MySendDataVideFrame(QPixmap)),NastroykaKamerDialog,SLOT(myShow(QPixmap)));//для отображения картинки

    }

    //третий поток
    if (tmp == "31"&&VideoPotok3&&VideoPotok3->StorogVideoPotok.OnPotok)
    {
        VideoPotok3->StorogVideoPotok.SendImege=true;
        connect(VideoPotok3, SIGNAL(MySendDataVideFrame(QPixmap)),NastroykaKamerDialog,SLOT(myShow(QPixmap)));//для отображения картинки

    }
    if (tmp == "30"&&VideoPotok3&&VideoPotok3->StorogVideoPotok.OnPotok)
    {
        VideoPotok3->StorogVideoPotok.SendImege=false;
        disconnect(VideoPotok3, SIGNAL(MySendDataVideFrame(QPixmap)),NastroykaKamerDialog,SLOT(myShow(QPixmap)));//для отображения картинки

    }

    //четвертый поток
    if (tmp == "41"&&VideoPotok4&&VideoPotok4->StorogVideoPotok.OnPotok)
    {
        VideoPotok4->StorogVideoPotok.SendImege=true;
        connect(VideoPotok4, SIGNAL(MySendDataVideFrame(QPixmap)),NastroykaKamerDialog,SLOT(myShow(QPixmap)));//для отображения картинки

    }
    if (tmp == "40"&&VideoPotok4&&VideoPotok4->StorogVideoPotok.OnPotok)
    {
        VideoPotok4->StorogVideoPotok.SendImege=false;
        disconnect(VideoPotok4, SIGNAL(MySendDataVideFrame(QPixmap)),NastroykaKamerDialog,SLOT(myShow(QPixmap)));//для отображения картинки

    }

    //пятый поток
    if (tmp == "51"&&VideoPotok5&&VideoPotok5->StorogVideoPotok.OnPotok)
    {
        VideoPotok5->StorogVideoPotok.SendImege=true;
        connect(VideoPotok5, SIGNAL(MySendDataVideFrame(QPixmap)),NastroykaKamerDialog,SLOT(myShow(QPixmap)));//для отображения картинки

    }
    if (tmp == "50"&&VideoPotok5&&VideoPotok5->StorogVideoPotok.OnPotok)
    {
        VideoPotok5->StorogVideoPotok.SendImege=false;
        disconnect(VideoPotok5, SIGNAL(MySendDataVideFrame(QPixmap)),NastroykaKamerDialog,SLOT(myShow(QPixmap)));//для отображения картинки

    }

    //шестый поток
    if (tmp == "61"&&VideoPotok6&&VideoPotok6->StorogVideoPotok.OnPotok)
    {
        VideoPotok6->StorogVideoPotok.SendImege=true;
        connect(VideoPotok6, SIGNAL(MySendDataVideFrame(QPixmap)),NastroykaKamerDialog,SLOT(myShow(QPixmap)));//для отображения картинки

    }
    if (tmp == "60"&&VideoPotok6&&VideoPotok6->StorogVideoPotok.OnPotok)
    {
        VideoPotok6->StorogVideoPotok.SendImege=false;
        disconnect(VideoPotok6, SIGNAL(MySendDataVideFrame(QPixmap)),NastroykaKamerDialog,SLOT(myShow(QPixmap)));//для отображения картинки

    }


}


void MainWindow::FTPAlarm()
{
    // qDebug()<<"Отработа ФТП Таймер";

    //  emit SlotLogView("Запустился ФТП Таймер (Тест удали сообщение)");

    //MyReadfile->WriteReports("2","15","16");
    QString tmpIN;
    QString tmpOUT;

    //  qDebug()<<"OnVideiopotok1 "<<OnVideiopotok1;

    emit DeleVideoFile();//почистим каталог с видеофайлами.


    if (OnVideiopotok1)
    {
        // qDebug()<<"Тест";
      //   emit SlotLogView("Переношу данные в файл, поток 1 (Тест удали сообщение)");
        tmpIN = QString::number(StorogVideoPotokMain[0].inPeople);//переносим в tmp чтобы не держать поток!
        tmpOUT =QString::number(StorogVideoPotokMain[0].outPeople);
        if (!MyReadfile->WriteReports("1",tmpIN,tmpOUT))
        {
         //   emit SlotLogView("MyReadfile->WriteReports - вернул false!!!!!!! (Тест удали сообщение)");
            return;//если не смог записать в файл выходим...
        }

        StorogVideoPotokMain[0].inPeople = 0;
        StorogVideoPotokMain[0].outPeople= 0;
      //  emit SlotLogView("Отработал \"Перенес данные в файл, поток 1\" (Тест удали сообщение)");
    }

    if (OnVideiopotok2)
    {
    //   emit SlotLogView("Переношу данные в файл, поток 2 !!!!ERROR!!!!! (Тест удали сообщение)");
        tmpIN = QString::number(StorogVideoPotokMain[1].inPeople);
        tmpOUT =QString::number(StorogVideoPotokMain[1].outPeople);
        if (!MyReadfile->WriteReports("2",tmpIN,tmpOUT))return;
        StorogVideoPotokMain[1].inPeople = 0;
        StorogVideoPotokMain[1].outPeople= 0;
    }

    if (OnVideiopotok3)
    {
        tmpIN = QString::number(StorogVideoPotokMain[2].inPeople);
        tmpOUT =QString::number(StorogVideoPotokMain[2].outPeople);
        if (!MyReadfile->WriteReports("3",tmpIN,tmpOUT))return;
        StorogVideoPotokMain[2].inPeople = 0;
        StorogVideoPotokMain[2].outPeople= 0;
    }

    if (OnVideiopotok4)
    {
        tmpIN = QString::number(StorogVideoPotokMain[3].inPeople);
        tmpOUT =QString::number(StorogVideoPotokMain[3].outPeople);
        if (!MyReadfile->WriteReports("4",tmpIN,tmpOUT))return;
        StorogVideoPotokMain[3].inPeople = 0;
        StorogVideoPotokMain[3].outPeople= 0;
    }

    if (OnVideiopotok5)
    {
        tmpIN = QString::number(StorogVideoPotokMain[4].inPeople);
        tmpOUT =QString::number(StorogVideoPotokMain[4].outPeople);
        if (!MyReadfile->WriteReports("5",tmpIN,tmpOUT))return;
        StorogVideoPotokMain[4].inPeople = 0;
        StorogVideoPotokMain[4].outPeople= 0;
    }

    if (OnVideiopotok6)
    {
        tmpIN = QString::number(StorogVideoPotokMain[5].inPeople);
        tmpOUT =QString::number(StorogVideoPotokMain[5].outPeople);
        if (!MyReadfile->WriteReports("6",tmpIN,tmpOUT))return;
        StorogVideoPotokMain[5].inPeople = 0;
        StorogVideoPotokMain[5].outPeople= 0;
    }

   emit PutFtp();

}




void MainWindow::StoragAlarm()
{
/*
qDebug()<<"--StoragAlarm--";
qDebug()<<TimeAnalis();
qDebug()<<VideoPotok1->StorogVideoPotok.OnPotok;
qDebug()<<"---------------";
*/
    //для потока 1
    if (OnVideiopotok1)//если вообще должен работать поток
    {
        //qDebug()<<"тест_01";

        if (TimeAnalis()) //если время рабочее
        {
            if (VideoPotok1->StorogVideoPotok.OnPotok)//поток создан
            {
                VideoPotok1->StorogVideoPotok.OnPotok= false;

            }
            else//поток не создан
            {
                /*
                connect(VideoPotok1,SIGNAL(SignalLogView(QString)),this,SLOT(SlotLogView(QString)));//для вывода в лог событий потока
                connect(this,SIGNAL(SignalExitThread_1()),VideoPotok1,SLOT(SlotExitThread()));
                VideoPotok1->start();//старт потока
                */
                StruktAllStartPotok.potok_1 =true;
                VideoPotok1->StorogVideoPotok.OnPotok= false;


            }


            if (VideoPotok1 && TimeAnalisTimeWriteVideo())//если функция для записи дает "добро"
            {
                VideoPotok1->StorogVideoPotok.WriteVideo =true;
            }
            else//иначе вырубаем запись
            {
                VideoPotok1->StorogVideoPotok.WriteVideo =false;
            }

        }
        else //время не рабочее
        {
            if (VideoPotok1->StorogVideoPotok.OnPotok)//но почемуто работает- убиваем
            {

                emit SlotLogView("Закончилось время работы камеры 1");
                VideoPotok1->StorogVideoPotok.WriteVideo =false;
                VideoPotok1->StorogVideoPotok.OnPotok=false;
                emit SlotPerenosDanuPotokAlarm();
                emit SlotConnektThreadVideo_1("10");
                timeTmp.start();   for(;timeTmp.elapsed() < 100;) {}//импровизированный таймер

                emit SignalExitThread_1();

                timeTmp.start();   for(;timeTmp.elapsed() < 50;) {}//импровизированный таймер
                disconnect(VideoPotok1,SIGNAL(SignalLogView(QString)),this,SLOT(SlotLogView(QString)));//для вывода в лог событий потока
                disconnect(this,SIGNAL(SignalExitThread_1()),VideoPotok1,SLOT(SlotExitThread()));

            }
            VideoPotok1->StorogVideoPotok.OnPotok= false;
        }

    }
    else//вообще не должне работать
    {
        if (VideoPotok1->StorogVideoPotok.OnPotok)//но почемуто работает- убиваем
        {

            emit SlotPerenosDanuPotokAlarm();
            emit SignalExitThread_1();
            timeTmp.start();   for(;timeTmp.elapsed() < 100;) {}//импровизированный таймер
            disconnect(VideoPotok1,SIGNAL(SignalLogView(QString)),this,SLOT(SlotLogView(QString)));//для вывода в лог событий потока
            disconnect(this,SIGNAL(SignalExitThread_1()),VideoPotok1,SLOT(SlotExitThread()));

        }
        VideoPotok1->StorogVideoPotok.OnPotok= false;


    }
/////////////////////////////////////////////////////////////////////////////////////
    //для потока 2


  //  timeTmp.start();   for(;timeTmp.elapsed() < 500;) {QApplication::processEvents();}//импровизированный таймер

    if (OnVideiopotok2)//если вообще должен работать поток
    {
        if (TimeAnalis()) //если время рабочее
        {
            if (VideoPotok2->StorogVideoPotok.OnPotok)//поток создан
            {
                VideoPotok2->StorogVideoPotok.OnPotok= false;
            }
            else//поток не создан
            {
                /*connect(VideoPotok2,SIGNAL(SignalLogView(QString)),this,SLOT(SlotLogView(QString)));//для вывода в лог событий потока
                connect(this,SIGNAL(SignalExitThread_2()),VideoPotok2,SLOT(SlotExitThread()));
                VideoPotok2->start();//старт потока
                */
                StruktAllStartPotok.potok_2 =true;
                VideoPotok2->StorogVideoPotok.OnPotok= false;
            }


            if (VideoPotok2 && TimeAnalisTimeWriteVideo())//если функция для записи дает "добро"
            {
                VideoPotok2->StorogVideoPotok.WriteVideo =true;
            }
            else//иначе вырубаем запись
            {
                VideoPotok2->StorogVideoPotok.WriteVideo =false;
            }

        }
        else //время не рабочее
        {
            if (VideoPotok2->StorogVideoPotok.OnPotok)//но почемуто работает- убиваем
            {
                emit SlotLogView("Закончилось время работы камеры 2");
                VideoPotok2->StorogVideoPotok.WriteVideo =false;
                VideoPotok2->StorogVideoPotok.OnPotok=false;
                emit SlotPerenosDanuPotokAlarm();
                emit SlotConnektThreadVideo_1("20");
                timeTmp.start();   for(;timeTmp.elapsed() < 100;) {}//импровизированный таймер

                emit SignalExitThread_2();

                timeTmp.start();   for(;timeTmp.elapsed() < 50;) {}//импровизированный таймер
                disconnect(VideoPotok2,SIGNAL(SignalLogView(QString)),this,SLOT(SlotLogView(QString)));//для вывода в лог событий потока
                disconnect(this,SIGNAL(SignalExitThread_2()),VideoPotok2,SLOT(SlotExitThread()));
            }
            VideoPotok2->StorogVideoPotok.OnPotok= false;
        }

    }
    else//вообще не должне работать
    {
        if (VideoPotok2->StorogVideoPotok.OnPotok)//но почемуто работает- убиваем
        {
            emit SlotPerenosDanuPotokAlarm();
            emit SignalExitThread_2();
            timeTmp.start();   for(;timeTmp.elapsed() < 100;) {}//импровизированный таймер
            disconnect(VideoPotok2,SIGNAL(SignalLogView(QString)),this,SLOT(SlotLogView(QString)));//для вывода в лог событий потока
            disconnect(this,SIGNAL(SignalExitThread_2()),VideoPotok2,SLOT(SlotExitThread()));
        }
        VideoPotok2->StorogVideoPotok.OnPotok= false;
    }
/////////////////////////////////////////////////////////////////////////////////////
    //для потока 3

 //   timeTmp.start();   for(;timeTmp.elapsed() < 500;) {QApplication::processEvents();}//импровизированный таймер
    if (OnVideiopotok3)//если вообще должен работать поток
    {
        if (TimeAnalis()) //если время рабочее
        {
            if (VideoPotok3->StorogVideoPotok.OnPotok)//поток создан
            {
                VideoPotok3->StorogVideoPotok.OnPotok= false;
            }
            else//поток не создан
            {
               StruktAllStartPotok.potok_3 =true;
                VideoPotok3->StorogVideoPotok.OnPotok= false;
            }


            if (VideoPotok3 && TimeAnalisTimeWriteVideo())//если функция для записи дает "добро"
            {
                VideoPotok3->StorogVideoPotok.WriteVideo =true;
            }
            else//иначе вырубаем запись
            {
                VideoPotok3->StorogVideoPotok.WriteVideo =false;
            }

        }
        else //время не рабочее
        {
            if (VideoPotok3->StorogVideoPotok.OnPotok)//но почемуто работает- убиваем
            {
                emit SlotLogView("Закончилось время работы камеры 3");
                VideoPotok3->StorogVideoPotok.WriteVideo =false;
                VideoPotok3->StorogVideoPotok.OnPotok=false;
                emit SlotPerenosDanuPotokAlarm();
                emit SlotConnektThreadVideo_1("30");
                timeTmp.start();   for(;timeTmp.elapsed() < 100;) {}//импровизированный таймер

                emit SignalExitThread_3();

                timeTmp.start();   for(;timeTmp.elapsed() < 50;) {}//импровизированный таймер
                disconnect(VideoPotok3,SIGNAL(SignalLogView(QString)),this,SLOT(SlotLogView(QString)));//для вывода в лог событий потока
                disconnect(this,SIGNAL(SignalExitThread_3()),VideoPotok3,SLOT(SlotExitThread()));
            }
            VideoPotok3->StorogVideoPotok.OnPotok= false;
        }

    }
    else//вообще не должне работать
    {
        if (VideoPotok3->StorogVideoPotok.OnPotok)//но почемуто работает- убиваем
        {
            emit SlotPerenosDanuPotokAlarm();
            emit SignalExitThread_3();
            timeTmp.start();   for(;timeTmp.elapsed() < 100;) {}//импровизированный таймер
            disconnect(VideoPotok3,SIGNAL(SignalLogView(QString)),this,SLOT(SlotLogView(QString)));//для вывода в лог событий потока
            disconnect(this,SIGNAL(SignalExitThread_3()),VideoPotok3,SLOT(SlotExitThread()));
        }
        VideoPotok3->StorogVideoPotok.OnPotok= false;
    }
/////////////////////////////////////////////////////////////////////////////////////
    //для потока 4


 //  timeTmp.start();   for(;timeTmp.elapsed() < 500;) {QApplication::processEvents();}//импровизированный таймер
    if (OnVideiopotok4)//если вообще должен работать поток
    {
        if (TimeAnalis()) //если время рабочее
        {
            if (VideoPotok4->StorogVideoPotok.OnPotok)//поток создан
            {
                VideoPotok4->StorogVideoPotok.OnPotok= false;
            }
            else//поток не создан
            {
                StruktAllStartPotok.potok_4 =true;
                VideoPotok4->StorogVideoPotok.OnPotok= false;
            }


            if (VideoPotok4 && TimeAnalisTimeWriteVideo())//если функция для записи дает "добро"
            {
                VideoPotok4->StorogVideoPotok.WriteVideo =true;
            }
            else//иначе вырубаем запись
            {
                VideoPotok4->StorogVideoPotok.WriteVideo =false;
            }

        }
        else //время не рабочее
        {
            if (VideoPotok4->StorogVideoPotok.OnPotok)//но почемуто работает- убиваем
            {
                emit SlotLogView("Закончилось время работы камеры 4");
                VideoPotok4->StorogVideoPotok.WriteVideo =false;
                VideoPotok4->StorogVideoPotok.OnPotok=false;
                emit SlotPerenosDanuPotokAlarm();
                emit SlotConnektThreadVideo_1("40");
                timeTmp.start();   for(;timeTmp.elapsed() < 100;) {}//импровизированный таймер

                emit SignalExitThread_4();

                timeTmp.start();   for(;timeTmp.elapsed() < 50;) {}//импровизированный таймер
                disconnect(VideoPotok4,SIGNAL(SignalLogView(QString)),this,SLOT(SlotLogView(QString)));//для вывода в лог событий потока
                disconnect(this,SIGNAL(SignalExitThread_4()),VideoPotok4,SLOT(SlotExitThread()));
            }
            VideoPotok4->StorogVideoPotok.OnPotok= false;
        }

    }
    else//вообще не должне работать
    {
        if (VideoPotok4->StorogVideoPotok.OnPotok)//но почемуто работает- убиваем
        {
            emit SlotPerenosDanuPotokAlarm();
            emit SignalExitThread_4();
            timeTmp.start();   for(;timeTmp.elapsed() < 100;) {}//импровизированный таймер
            disconnect(VideoPotok4,SIGNAL(SignalLogView(QString)),this,SLOT(SlotLogView(QString)));//для вывода в лог событий потока
            disconnect(this,SIGNAL(SignalExitThread_4()),VideoPotok4,SLOT(SlotExitThread()));
        }
        VideoPotok4->StorogVideoPotok.OnPotok= false;
    }

/////////////////////////////////////////////////////////////////////////////////////


    //для потока 5
  //  timeTmp.start();   for(;timeTmp.elapsed() < 500;) {QApplication::processEvents();}//импровизированный таймер
    if (OnVideiopotok5)//если вообще должен работать поток
    {
        if (TimeAnalis()) //если время рабочее
        {
            if (VideoPotok5->StorogVideoPotok.OnPotok)//поток создан
            {
                VideoPotok5->StorogVideoPotok.OnPotok= false;
            }
            else//поток не создан
            {
                StruktAllStartPotok.potok_5 =true;
                VideoPotok5->StorogVideoPotok.OnPotok= false;
            }


            if (VideoPotok5 && TimeAnalisTimeWriteVideo())//если функция для записи дает "добро"
            {
                VideoPotok5->StorogVideoPotok.WriteVideo =true;
            }
            else//иначе вырубаем запись
            {
                VideoPotok5->StorogVideoPotok.WriteVideo =false;
            }

        }
        else //время не рабочее
        {
            if (VideoPotok5->StorogVideoPotok.OnPotok)//но почемуто работает- убиваем
            {
                emit SlotLogView("Закончилось время работы камеры 5");
                VideoPotok5->StorogVideoPotok.WriteVideo =false;
                VideoPotok5->StorogVideoPotok.OnPotok=false;
                emit SlotPerenosDanuPotokAlarm();
                emit SlotConnektThreadVideo_1("50");
                timeTmp.start();   for(;timeTmp.elapsed() < 100;) {}//импровизированный таймер

                emit SignalExitThread_5();

                timeTmp.start();   for(;timeTmp.elapsed() < 50;) {}//импровизированный таймер
                disconnect(VideoPotok5,SIGNAL(SignalLogView(QString)),this,SLOT(SlotLogView(QString)));//для вывода в лог событий потока
                disconnect(this,SIGNAL(SignalExitThread_5()),VideoPotok5,SLOT(SlotExitThread()));
            }
            VideoPotok5->StorogVideoPotok.OnPotok= false;
        }

    }
    else//вообще не должне работать
    {
        if (VideoPotok5->StorogVideoPotok.OnPotok)//но почемуто работает- убиваем
        {
            emit SlotPerenosDanuPotokAlarm();
            emit SignalExitThread_5();
            timeTmp.start();   for(;timeTmp.elapsed() < 100;) {}//импровизированный таймер
            disconnect(VideoPotok5,SIGNAL(SignalLogView(QString)),this,SLOT(SlotLogView(QString)));//для вывода в лог событий потока
            disconnect(this,SIGNAL(SignalExitThread_5()),VideoPotok4,SLOT(SlotExitThread()));
        }
        VideoPotok5->StorogVideoPotok.OnPotok= false;
    }
/////////////////////////////////////////////////////////////////////////////////////


    //для потока 6
  //  timeTmp.start();   for(;timeTmp.elapsed() < 500;) {QApplication::processEvents();}//импровизированный таймер
    if (OnVideiopotok6)//если вообще должен работать поток
    {
        if (TimeAnalis()) //если время рабочее
        {
            if (VideoPotok6->StorogVideoPotok.OnPotok)//поток создан
            {
                VideoPotok6->StorogVideoPotok.OnPotok= false;
            }
            else//поток не создан
            {
                StruktAllStartPotok.potok_6 =true;
                VideoPotok6->StorogVideoPotok.OnPotok= false;
            }


            if (VideoPotok6 && TimeAnalisTimeWriteVideo())//если функция для записи дает "добро"
            {
                VideoPotok6->StorogVideoPotok.WriteVideo =true;
            }
            else//иначе вырубаем запись
            {
                VideoPotok6->StorogVideoPotok.WriteVideo =false;
            }

        }
        else //время не рабочее
        {
            if (VideoPotok6->StorogVideoPotok.OnPotok)//но почемуто работает- убиваем
            {
                emit SlotLogView("Закончилось время работы камеры 6");
                VideoPotok6->StorogVideoPotok.WriteVideo =false;
                VideoPotok6->StorogVideoPotok.OnPotok=false;
                emit SlotPerenosDanuPotokAlarm();
                emit SlotConnektThreadVideo_1("60");
                timeTmp.start();   for(;timeTmp.elapsed() < 100;) {}//импровизированный таймер

                emit SignalExitThread_6();

                timeTmp.start();   for(;timeTmp.elapsed() < 50;) {}//импровизированный таймер
                disconnect(VideoPotok6,SIGNAL(SignalLogView(QString)),this,SLOT(SlotLogView(QString)));//для вывода в лог событий потока
                disconnect(this,SIGNAL(SignalExitThread_6()),VideoPotok6,SLOT(SlotExitThread()));
            }
            VideoPotok6->StorogVideoPotok.OnPotok= false;
        }

    }
    else//вообще не должне работать
    {
        if (VideoPotok6->StorogVideoPotok.OnPotok)//но почемуто работает- убиваем
        {
            emit SlotPerenosDanuPotokAlarm();
            emit SignalExitThread_6();
            timeTmp.start();   for(;timeTmp.elapsed() < 100;) {}//импровизированный таймер
            disconnect(VideoPotok6,SIGNAL(SignalLogView(QString)),this,SLOT(SlotLogView(QString)));//для вывода в лог событий потока
            disconnect(this,SIGNAL(SignalExitThread_6()),VideoPotok6,SLOT(SlotExitThread()));
        }
        VideoPotok6->StorogVideoPotok.OnPotok= false;
    }


}

void MainWindow::SlotPerenosDanuPotokAlarm()//синхронизирует, переносит даные, кол прошедших людей.
{
    emit SlotAllStartPotok(); //запустим потоки если есть что запускать!!
    // qDebug()<<"SlotPerenosDanuPotokAlarm()";
    if (VideoPotok1&&VideoPotok1->StorogVideoPotok.OnPotok)
    {
        StorogVideoPotokMain[0].inPeople += VideoPotok1->StorogVideoPotok.inPeople;
        VideoPotok1->StorogVideoPotok.inPeople =0;
        StorogVideoPotokMain[0].outPeople += VideoPotok1->StorogVideoPotok.outPeople;
        VideoPotok1->StorogVideoPotok.outPeople =0;

        //  qDebug()<< "вошло"<<StorogVideoPotokMain[0].inPeople;
        //   qDebug()<< "вышло"<<StorogVideoPotokMain[0].outPeople;
    }
    if (VideoPotok2&&VideoPotok2->StorogVideoPotok.OnPotok)
    {
        StorogVideoPotokMain[1].inPeople += VideoPotok2->StorogVideoPotok.inPeople;
        VideoPotok2->StorogVideoPotok.inPeople =0;
        StorogVideoPotokMain[1].outPeople += VideoPotok2->StorogVideoPotok.outPeople;
        VideoPotok2->StorogVideoPotok.outPeople =0;
    }

    if (VideoPotok3&&VideoPotok3->StorogVideoPotok.OnPotok)
    {
        StorogVideoPotokMain[2].inPeople += VideoPotok3->StorogVideoPotok.inPeople;
        VideoPotok3->StorogVideoPotok.inPeople =0;
        StorogVideoPotokMain[2].outPeople += VideoPotok3->StorogVideoPotok.outPeople;
        VideoPotok3->StorogVideoPotok.outPeople =0;
    }
    if (VideoPotok4&&VideoPotok4->StorogVideoPotok.OnPotok)
    {
        StorogVideoPotokMain[3].inPeople += VideoPotok4->StorogVideoPotok.inPeople;
        VideoPotok4->StorogVideoPotok.inPeople =0;
        StorogVideoPotokMain[3].outPeople += VideoPotok4->StorogVideoPotok.outPeople;
        VideoPotok4->StorogVideoPotok.outPeople =0;
    }
    if (VideoPotok5&&VideoPotok5->StorogVideoPotok.OnPotok)
    {
        StorogVideoPotokMain[4].inPeople += VideoPotok5->StorogVideoPotok.inPeople;
        VideoPotok5->StorogVideoPotok.inPeople =0;
        StorogVideoPotokMain[4].outPeople += VideoPotok5->StorogVideoPotok.outPeople;
        VideoPotok5->StorogVideoPotok.outPeople =0;
    }
    if (VideoPotok6&&VideoPotok6->StorogVideoPotok.OnPotok)
    {
        StorogVideoPotokMain[5].inPeople += VideoPotok6->StorogVideoPotok.inPeople;
        VideoPotok6->StorogVideoPotok.inPeople =0;
        StorogVideoPotokMain[5].outPeople += VideoPotok6->StorogVideoPotok.outPeople;
        VideoPotok6->StorogVideoPotok.outPeople =0;
    }


}

void MainWindow::DeleVideoFile()//удаляет старые файлы видео записи
{

emit SlotLogView("Запустилась чистка виде файлов");
    QDir dir;


    int countFile = 24;//количесвто допустимых файлов

    if(!dir.cd(settingsReestr->value("Catalog","0").toString()+"\\video\\"))//устанавливаем каталог поиска
    {
        //qDebug()<<"не смог открыть каталог с файлами";
        emit SlotLogView("Не смог открыть каталог с видеофайлами (для анализа и дальнейшего удаления)");
        return;

    }

    else
    {
        //инициализация перменных
        QStringList tmp;//хранилище всех путей
        int j=0;//номера строк в QStringList
        QString TmpPutkFile;
        int NomerSimvola;
        QDate dateFile;
        QDate dateFileTmp(2018,12,31);//имя самого молодого файла
        int NomerFileTmp;//порядковый номер самого старого файла  в tmp
        QStringList nameFilter;
        nameFilter<<"*.avi";//устанавливаем фильтр для поиска

        // QStringList listFiles= dir.entryList();//все файлы
        QStringList listFiles =  dir.entryList(nameFilter, QDir::Files);//только файлы и по маске.
        foreach (QString file, listFiles)
        {
            tmp << dir.absoluteFilePath(file);//загоняем найденые в хранилище
        }

        // qDebug()<<"количество найденых файлов " <<tmp.size();
        QListIterator<QString> i(tmp);//создаем индексацию QStringList

        //qDebug()<<tmp.size()-countFile;
        //qDebug()<<countFile;
        //int tmp2 =tmp.size();

        if (tmp.size()>countFile)//если файлов больше чем разрешено... то удаляем самый "старый"
            //if (countFile<=3);//если файлов больше чем разрешено... то удаляем самый "старый"
        {
            while (i.hasNext())//пробигаем по хранилищу
            {
                TmpPutkFile = tmp.at(j);
                //qDebug()<<TmpPutkFile;
                NomerSimvola = TmpPutkFile.length()-25;//от конца отсчитываем 25 симвоволов (имя файла 05.12.2014_12.28.56_2.avi)

                if(NomerSimvola>=0)//если найден
                {
                    //qDebug()<< TmpPutkFile.at(NomerSimvola)<< TmpPutkFile.at(NomerSimvola+1);
                    //05.12.2014_12.28.56_2.avi
                    QString dayS ;
                    dayS+=TmpPutkFile.at(NomerSimvola);
                    dayS+=TmpPutkFile.at(NomerSimvola+1);
                    int day =   dayS.toInt();

                    QString monthS ;
                    monthS+=TmpPutkFile.at(NomerSimvola+3);
                    monthS+=TmpPutkFile.at(NomerSimvola+4);
                    int month =   monthS.toInt();


                    QString yearS ;
                    yearS+=TmpPutkFile.at(NomerSimvola+6);
                    yearS+=TmpPutkFile.at(NomerSimvola+7);
                    yearS+=TmpPutkFile.at(NomerSimvola+8);
                    yearS+=TmpPutkFile.at(NomerSimvola+9);
                    int year =   yearS.toInt();

                    dateFile.setDate(year,month,day);
                    // qDebug()<<dateFile;
                    if (dateFile<dateFileTmp)//если найденый файл моложе...
                    {
                        dateFileTmp=dateFile;//запомнил дату файла для дальнейшего удаления
                        NomerFileTmp = j; //запомнил номер для дальнейшего удаления
                    }
                }

                if(j<tmp.size()-1) j++;//ограничитель выхода за пределы массива!
                else break;
            }
            // qDebug()<<"нашел "<<dateFileTmp<<" номер файла "<<tmp.at(NomerFileTmp);
            emit SlotLogView("Удалил файл " + tmp.at(NomerFileTmp) );

            QFile::remove(tmp.at(NomerFileTmp));

        }


    }
  //  emit SlotLogView("Отработал DeleVideoFile (Тест удали сообщение)");


}

void MainWindow::SlotAllStartPotok()//одновренменный запус всех потоков(качели что не зависал)
{


    if (StruktAllStartPotok.potok_1)
    {
        connect(VideoPotok1,SIGNAL(SignalLogView(QString)),this,SLOT(SlotLogView(QString)));//для вывода в лог событий потока
        connect(this,SIGNAL(SignalExitThread_1()),VideoPotok1,SLOT(SlotExitThread()));
        VideoPotok1->start();//старт потока
        StruktAllStartPotok.potok_1 =false;
        return;
    }
    if (StruktAllStartPotok.potok_2)
    {
        connect(VideoPotok2,SIGNAL(SignalLogView(QString)),this,SLOT(SlotLogView(QString)));//для вывода в лог событий потока
        connect(this,SIGNAL(SignalExitThread_2()),VideoPotok2,SLOT(SlotExitThread()));
        VideoPotok2->start();//старт потока
        StruktAllStartPotok.potok_2 =false;
        return;
    }
    if (StruktAllStartPotok.potok_3)
    {
        connect(VideoPotok3,SIGNAL(SignalLogView(QString)),this,SLOT(SlotLogView(QString)));//для вывода в лог событий потока
        connect(this,SIGNAL(SignalExitThread_3()),VideoPotok3,SLOT(SlotExitThread()));
        VideoPotok3->start();//старт потока
        StruktAllStartPotok.potok_3 =false;
        return;
    }
    if (StruktAllStartPotok.potok_4)
    {
        connect(VideoPotok4,SIGNAL(SignalLogView(QString)),this,SLOT(SlotLogView(QString)));//для вывода в лог событий потока
        connect(this,SIGNAL(SignalExitThread_4()),VideoPotok4,SLOT(SlotExitThread()));
        VideoPotok4->start();//старт потока
        StruktAllStartPotok.potok_4 =false;
        return;
    }
    if (StruktAllStartPotok.potok_5)
    {
        connect(VideoPotok5,SIGNAL(SignalLogView(QString)),this,SLOT(SlotLogView(QString)));//для вывода в лог событий потока
        connect(this,SIGNAL(SignalExitThread_5()),VideoPotok5,SLOT(SlotExitThread()));
        VideoPotok5->start();//старт потока
        StruktAllStartPotok.potok_5 =false;
        return;
    }
    if (StruktAllStartPotok.potok_6)
    {
        connect(VideoPotok6,SIGNAL(SignalLogView(QString)),this,SLOT(SlotLogView(QString)));//для вывода в лог событий потока
        connect(this,SIGNAL(SignalExitThread_6()),VideoPotok6,SLOT(SlotExitThread()));
        VideoPotok6->start();//старт потока
        StruktAllStartPotok.potok_6 =false;
        return;
    }

    /* StruktAllStartPotok

        bool potok_1;
        bool potok_2;
        bool potok_3;
        bool potok_4;
        bool potok_5;
        bool potok_6;
        */
}

void MainWindow::PutFtp()
{
  // emit SlotLogView("-----------------------------------------------");
 //   emit SlotLogView("Запустился \"PutFtp()\" (Тест удали сообщение)");

    if(FtpFlag)
    {
       // qDebug()<<AllFTPAlarm;
        if (AllFTPAlarm<2)//отправка каждые 15 минут
        {
            myFtp = new Ftp();
            connect(myFtp,SIGNAL(SignalLogView(QString)),this,SLOT(SlotLogView(QString)));
            connect(myFtp, SIGNAL(finished()), myFtp, SLOT(terminate()));
          //  emit SlotLogView("Запустился \"Отправка одного отчетного файла\" (Тест удали сообщение)");

            myFtp->start();
            emit SlotLogView("Отправил отчет на ФТП (каждые "+ TimeLogFtp+" секунд)");

            AllFTPAlarm +=1;
        }
        else
        {
           myFtp = new Ftp();
            connect(myFtp,SIGNAL(SignalLogView(QString)),this,SLOT(SlotLogView(QString)));
            connect(myFtp, SIGNAL(finished()), myFtp, SLOT(terminate()));
         //  emit SlotLogView("Запустился \"Отправка всех отчетных файлов\" (Тест удали сообщение)");
            myFtp->AllLogs=true;
            myFtp->start();
            emit SlotLogView("Отправил Все отчет на ФТП (каждые "+ QString::number(TimeLogFtp.toInt()*AllFTPAlarm)+" секунд)");
            AllFTPAlarm =0;
            myFtp->AllLogs=false;
        }

        //myFtp->GetAllFile();
      //   QtConcurrent::run(myFtp, &Ftp::GetAllFile);
      //  emit SlotLogView("Отправил Все отчет на ФТП (каждые 5 часов)");

    }
  //  emit SlotLogView("Отработал \"PutFtp()\" (Тест удали сообщение)");
}

void MainWindow::LisCensiy()
{
    QDate tmp  = QDate::currentDate();
    if (tmp.year()> 2016)
    {
        QMessageBox::critical(NULL,QObject::tr("Беда..."),tr("Пора купить лицензию"));
        this->deleteLater();
    }

}

bool MainWindow::TimeAnalisTimeWriteVideo()//анализируем время записи видео
{
    if(WriteVideio)//если запись включена то...
    {
        timeSystem = QTime::currentTime();//получаем текущее время системы

        if (timeSystem>timeOnWriteVideo && timeSystem<timeOffWriteVideo )
        {
            return true;
        }
        return false;
    }
    return false;
}


void MainWindow::on_action2_triggered()
{
    // qDebug()<<"Меню настройка ФТП";
    ftpDialog = new FTPDialog();//диалоговое окна настройки ФТП!

    ftpDialog->show();
}

void MainWindow::on_action_3_triggered()
{
    //  qDebug()<<"Меню настройка параметров";
    MyNastrParamKamDialog = new NastrParamKamDialog();//диалоговое окно настройки параметров
    MyNastrParamKamDialog->show();

}

void MainWindow::initPainter()
{

    //инициализация каталога расположение каталога с прогой
    settingsReestr = new QSettings("HKEY_CURRENT_USER\\Software\\SPP Gav\\Settings",
                                   QSettings::NativeFormat,this);

    //и так по всем потокам обнулить переменные
    StorogVideoPotokMain[0].inPeople = 0;
    StorogVideoPotokMain[0].outPeople = 0;

    StorogVideoPotokMain[1].inPeople = 0;
    StorogVideoPotokMain[1].outPeople = 0;

    StorogVideoPotokMain[2].inPeople = 0;
    StorogVideoPotokMain[2].outPeople = 0;

    StorogVideoPotokMain[3].inPeople = 0;
    StorogVideoPotokMain[3].outPeople = 0;

    StorogVideoPotokMain[4].inPeople = 0;
    StorogVideoPotokMain[4].outPeople = 0;

    StorogVideoPotokMain[5].inPeople = 0;
    StorogVideoPotokMain[5].outPeople = 0;


    if (MyReadfile->ReadSetting("Keym24","1")== "on")OnVideiopotok1 =true;
    else OnVideiopotok1 =false;

    if (MyReadfile->ReadSetting("Keym24","2")== "on")OnVideiopotok2 =true;
    else OnVideiopotok2 =false;

    if (MyReadfile->ReadSetting("Keym24","3")== "on")OnVideiopotok3 =true;
    else OnVideiopotok3 =false;

    if (MyReadfile->ReadSetting("Keym24","4")== "on")OnVideiopotok4 =true;
    else OnVideiopotok4 =false;

    if (MyReadfile->ReadSetting("Keym24","5")== "on")OnVideiopotok5 =true;
    else OnVideiopotok5 =false;

    if (MyReadfile->ReadSetting("Keym24","6")== "on")OnVideiopotok6 =true;
    else OnVideiopotok6 =false;


    //проверяем запуск фтп клиента
    if ( MyReadfile->ReadSetting("Keyt23","1")=="on")FtpFlag = true;
    else FtpFlag = false;
    //qDebug()<<FtpFlag;

    TimeAnalis("loadtime"); // задаем время работы из файла!

    /////
    if (MyReadfile->ReadSetting("Keyq26","1")== "on")
    {
        WriteVideio =true;//записывать видео
    }
    else WriteVideio =false;

    timeOnWriteVideo.setHMS((MyReadfile->ReadSetting("Keyz27","1")).toInt(),
                            (MyReadfile->ReadSetting("Keyx28","1")).toInt(),
                            0);
    timeOffWriteVideo.setHMS((MyReadfile->ReadSetting("Keyc29","1")).toInt(),
                             (MyReadfile->ReadSetting("Keyv30","1")).toInt(),
                             0);


    /////
     StruktAllStartPotok.potok_1 = false;
     StruktAllStartPotok.potok_2= false;
     StruktAllStartPotok.potok_3= false;
     StruktAllStartPotok.potok_4= false;
     StruktAllStartPotok.potok_5= false;
     StruktAllStartPotok.potok_6= false;

     AllFTPAlarm = 0;

}

bool MainWindow::TimeAnalis(QString tmp )
{

    if (tmp == "loadtime")//задать время из настроек
    {
        timeON.setHMS((MyReadfile->ReadSetting("Keyz18","1")).toInt(),(MyReadfile->ReadSetting("Keyx19","1")).toInt(),0);
        timeOFF.setHMS((MyReadfile->ReadSetting("Keyc20","1")).toInt(),(MyReadfile->ReadSetting("Keyv21","1")).toInt(),0);
        // qDebug()<<"timeON "<<timeON;
        // qDebug()<<"timeOFF "<<timeOFF;
        return false;
    }

    timeSystem = QTime::currentTime();//получаем текущее время системы

    //если нынешней время больше время вкл и меньше времени выкл
    if (timeSystem>timeON && timeSystem<timeOFF )
    {
        return true;
    }
    return false;
}



void MainWindow::on_pushButton_3_clicked() //очистить лог
{
   ui->textEdit->clear();
     // myFtp->OtpravkaFTP_2(NULL);
   // emit PutFtp();
  // emit LisCensiy();

//emit StoragAlarm();

   //emit  FTPAlarm();
   // qDebug()<<myFtp->PoiskPosledyuFail(settingsReestr->value("Catalog","0").toString()+"\\reports\\","*.txt",MyReadfile->ReadSetting("Keyy05","1"));


   // for (int i (0); i<1000; i++)
  //  {
     //  emit FTPAlarm();;
      //   timeTmp.start();   for(;timeTmp.elapsed() < 10000;) {}//импровизированный таймер

  //  }





    //qDebug()<<"Тест";
    // myFtp->GetAllFile();
    //    MyReadfile->WriteReports("1","12","13");
  //  MyReadfile->PerviyStartParametr();
    //    myFtp->MyRun();//если включена отправка отчета по ФТП
    //MyReadfile->WriteReports("1","10","22");
    //DeleVideoFile();
    // MyReadfile->VriteSetting("Keyy05","0001212","1");
    //  MyReadfile->VriteSetting("Keyh15","70","1");
    // MyReadfile->VriteSetting("Key22","345@12","2");
    // qDebug()<< MyReadfile->ReadSetting("Key22","1");
    //MyReadfile->myCryptTmp("slon",1);
    //MyReadfile->myCryptTmp(MyReadfile->myCryptTmp("slon",1),0);
    //  qDebug()<<"считал - " <<MyReadfile->ReadSetting("Keyi07","1");
    // qDebug()<<"считал - " <<MyReadfile->ReadSetting("Keyh15","1");
}

void MainWindow::on_action_triggered()
{
    // qDebug()<<"Меню настройка сети";
    myPing = new Ping();//диалоговое окно настройки сети
    myPing->show();
}

void MainWindow::on_action_2_triggered()//о программе
{
    MyInfo * myinfo;
    myinfo = new MyInfo();
    myinfo->show();
}
