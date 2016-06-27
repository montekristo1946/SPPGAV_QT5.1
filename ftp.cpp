#include "ftp.h"

Ftp::Ftp(QObject *parent) :
    QThread(parent)
{
    //задаем параметры settings, для чтения каталога проги в реестре
    settingsReestr = new QSettings("HKEY_CURRENT_USER\\Software\\SPP Gav\\Settings",
                                   QSettings::NativeFormat,this);

    ImyFile = settingsReestr->value("Catalog","0").toString()+"\\reports\\";

    moveToThread(this);
   Readfile * MyReadfile;
    MyReadfile =new Readfile();
    AllLogs = false;


    LoginFtp    = MyReadfile->ReadSetting("Keyw02","1");//логин
    PasswordFtp =  MyReadfile->ReadSetting("Keyq01","1");//пароль
    port            = MyReadfile->ReadSetting("Keye03","1").toInt();//порт
    UrlSetting  =MyReadfile->ReadSetting("Keyr04","1");//ftp://ftp.ru
    IDD =        MyReadfile->ReadSetting("Keyy05","1");

    delete MyReadfile;
    settingsReestr->deleteLater();

   // emit SignalLogView("Конструктор Ftp");

    timerDeletClass = new QTimer;
     timerDeletClass->start(120000);







}

void Ftp::run()
{
   connect(timerDeletClass, SIGNAL(timeout()), this, SLOT(SlotStorag()));
   connect(this, SIGNAL(SignalStopAlarm()), timerDeletClass, SLOT(stop()));

qDebug()<<AllLogs;
    if (AllLogs)
    {
        // qDebug()<<"metka 2";
        AllLogs=false;

        OtpravkaFTP_2("all");//если стоит флаг отправить все файлы
    }

    else
    {
       OtpravkaFTP_2(); //  qDebug()<<"metka 1";

    }

    emit SlotExitThread();


   exec();
}

Ftp::~Ftp()
{
    qDebug()<<"Диструктор Ftp";

}


bool Ftp::OtpravkaFTP_2(QString setting)
{
  // emit SignalLogView("Метка OtpravkaFTP_2  1 ");

    QStringList tmp;//хранилище всех путей
    QStringList PutiNaOtpravku;//хранилище всех путей



    QDir dir;
    if (!dir.cd(ImyFile))//устанавливаем каталог поиска
    {
        //qDebug()<<"не нашел каталог с \\reports\\ ";
        emit SignalLogView("Не нашел каталог с \\reports\\ (класс Ftp) ");
        //SlotExitThread();
        return false;
    }

    QStringList nameFilter;
    nameFilter<<"*.txt";//устанавливаем фильтр для поиска

    // QStringList listFiles= dir.entryList();//все файлы
    QStringList listFiles =  dir.entryList(nameFilter, QDir::Files);//только файлы и по маске.
    foreach (QString file, listFiles)
    {
        tmp << dir.absoluteFilePath(file);//загоняем найденые в хранилище
    }

    if (tmp.empty())
    {
       // qDebug()<<"нет файлов .txt в каталоге  \\reports\\ ";
         emit SignalLogView("Нет файлов .txt в каталоге  \\reports\\ (класс Ftp) ");
        //SlotExitThread();
        return false;
    }
    QListIterator<QString> i(tmp);//создаем индексацию QStringList

    int j=0;//номера строк в QStringList
    while (i.hasNext())//пробигаем по хранилищу
    {
        int NomerSimvola;
        NomerSimvola = i.next().indexOf(QRegExp(IDD));//ищем строку в которой есть IDD
        if(NomerSimvola>=0)//если найден IDD
        {

            if (!ObrabotkaHranilicha_2(&PutiNaOtpravku,tmp.at(j)))
            {
               // qDebug()<<"не смог обработать хранилище ";
                emit SignalLogView("Не смог обработать хранилище (класс Ftp) ");
                 //SlotExitThread();
                return false;
            }
        }

        j++;

    }


    nameFilter.clear();
    listFiles.clear();
    tmp.clear();


    if (setting == "all")//отправляем все файлы
    {
        int NomerSimvola;
        for (int i(0);i<PutiNaOtpravku.count();i++)
        {
         //qDebug()<< PutiNaOtpravku.at(i);
         NomerSimvola = PutiNaOtpravku.at(i).indexOf(QRegExp(IDD));
         if(!GetFile(LoginFtp,PasswordFtp,port,UrlSetting,PutiNaOtpravku.at(i).mid(NomerSimvola)))//функция отрпавки
            {
             emit SignalLogView("не смог отправить все файлы (класс Ftp) ");
            // SlotExitThread();
             break;
            }
        }
        // emit SignalLogView("Метка OtpravkaFTP_2  2_2 ");
        PutiNaOtpravku.clear();
        //SlotExitThread();
        return true;


    }
    else
    {

        GetFile(LoginFtp,PasswordFtp,port,UrlSetting,PoiskPosledyuFail_2(&PutiNaOtpravku));//функция отрпавки
       //   emit SignalLogView("Метка OtpravkaFTP_2  2_1 ");
        //SlotExitThread();
        return true;

    }



}

bool Ftp::ObrabotkaHranilicha_2(QStringList *inHranlish, QString inPutFile)//добавляет в хранилище новые строки (удаляя самые старые)
{
     // emit SignalLogView("Метка ObrabotkaHranilicha_2  1 ");
    if (inPutFile!="")// && inPutFile.indexOf(QRegExp(IDD))!=-1)//если есть входной параметр то добавляем строку
    {
        if (inHranlish->isEmpty()||inHranlish->count()<3 )//если списо абсолютных путей пуст или мало для сравнения
        {
            inHranlish->append(inPutFile);
            return true;

        }
        else
        {
            QDate Date;
            Date.setDate(9999,1,1);

            QDate DateTmp;

            int PosiziyUdaleniy(0);

            for(int g(0);g<inHranlish->count();g++)//пробигаем по хранилищу ишем самый старый файл
            {
                int NomerSimvola = inHranlish->at(g).indexOf(QRegExp(IDD));

                DateTmp.setDate(inHranlish->at(g).mid(NomerSimvola+8,4).toInt(),
                                inHranlish->at(g).mid(NomerSimvola+8+4,2).toInt(),
                                inHranlish->at(g).mid(NomerSimvola+8+4+2,2).toInt());//устанавливаем дату во временную переменную

                if (Date>DateTmp)
                {
                    Date=DateTmp;
                    PosiziyUdaleniy=g;

                }

            }
            inHranlish->removeAt(PosiziyUdaleniy);
            inHranlish->append(inPutFile);
          //  emit SignalLogView("Метка ObrabotkaHranilicha_2  2_1 ");
            return true;
        }
    }
   // emit SignalLogView("Метка ObrabotkaHranilicha_2  2_2 ");
    return false;

}

QString Ftp::PoiskPosledyuFail_2(QStringList *inHranlish)
{
//emit SignalLogView("Метка PoiskPosledyuFail_2  1 ");

    if (inHranlish->count()>0)
    {
    QDate Date;
    Date.setDate(0,0,0);

    QDate DateTmp;

    int PosiziyUdaleniy(0);

    for(int g(0);g<inHranlish->count();g++)//пробигаем по хранилищу ишем самый старый файл
    {
        int NomerSimvola = inHranlish->at(g).indexOf(QRegExp(IDD));

        DateTmp.setDate(inHranlish->at(g).mid(NomerSimvola+8,4).toInt(),
                        inHranlish->at(g).mid(NomerSimvola+8+4,2).toInt(),
                        inHranlish->at(g).mid(NomerSimvola+8+4+2,2).toInt());//устанавливаем дату во временную переменную

        if (Date<DateTmp)
        {
            Date=DateTmp;
            PosiziyUdaleniy=g;

        }

    }

    int NomerSimvola = inHranlish->at(PosiziyUdaleniy).indexOf(QRegExp(IDD));
   // emit SignalLogView("Метка PoiskPosledyuFail_2  2_1 ");
    return inHranlish->at(PosiziyUdaleniy).mid(NomerSimvola);
    }
    //emit SignalLogView("Метка PoiskPosledyuFail_2  2_2 ");
    return "Error PoiskPosledyuFail_2 Нет файлов в inHranlish";
}

void Ftp::doCleaning()
{
    // if( reply != NULL )
    // {
    reply->deleteLater();
    manager->deleteLater();

    //qDebug()<<"Метка 2 reply != NULL";
    //}
}

void Ftp::SlotExitThread()
{

    //emit SignalLogView("Разрушился поток ФТП ");

    emit SignalStopAlarm();
  //  timerDeletClass->deleteLater();

     this->destroyed();

     this->quit();
     this->wait();
    //this->sleep(30);

   // delete this;
  //  this->deleteLater();
   // this->terminate();

}

void Ftp::SlotStorag()
{
  /* emit doCleaning();
   emit SignalLogView("Зависла передача файла FTP");
   emit SlotExitThread();*/
    emit SignalLogView("Завис поток FTP");
    emit SignalStorag();


}

void Ftp::SlotVievDownload(qint64 tekush, qint64 total)
{
    //qDebug()<<tekush<<" из "<<total;
    emit SignalLogView(" Отравлено на ФТП (байт) " +QString::number(tekush)+ " из "+QString::number(total));

}

void Ftp::SlotErrorDownload(QNetworkReply::NetworkError error)
{
   //qDebug()<< "Ошибка SlotErrorDounload" <<error;
   if (error == 204)
      emit SignalLogView("Error FTP Сервера,  FTP просит проверку подлиности ");

   if (error ==  5)
       emit SignalLogView("Error FTP Сервера, Прервано таймером зависания");

   if  (error != 204 || error != 5)
       emit SignalLogView("Error FTP Сервера,№ "+QString::number(error) );

}

bool Ftp::GetFile(QString LoginFtp, QString PasswordFtp,int port,QString UrlFtp,QString FileOutFtp)
{
  //  emit SignalLogView("Метка GetFile 1_1 ");
    QUrl url(UrlFtp+FileOutFtp);

    url.setUserName(LoginFtp);
    url.setPassword(PasswordFtp);
    url.setPort(port);

  //  emit SignalLogView("Метка GetFile 1_2 " +UrlFtp+" "+FileOutFtp+" "+LoginFtp +" "+PasswordFtp+" "+QString::number(port));


    QFile    file(ImyFile+FileOutFtp);
   // emit SignalLogView("Метка GetFile 1_3 " + ImyFile+FileOutFtp);

    if (!file.open(QIODevice::ReadOnly))
    {
        emit SignalLogView ("Не нашел файл для отправки на ФТП "+ImyFile+FileOutFtp);
        return false;
    }
    QByteArray *buf = new QByteArray();
    *buf =  file.readAll();

    file.close();
  //  emit SignalLogView("Метка GetFile 1_4 ");

    manager = new QNetworkAccessManager(this);

    reply = manager->put(QNetworkRequest(url),*buf);
    QEventLoop  loop;

    QObject::connect(reply,SIGNAL(finished()),&loop,SLOT(quit()));//при завершении закачки закртыие
    QObject::connect(this,SIGNAL(SignalStorag()),reply,SLOT(abort()));
    //QObject::connect(this,SIGNAL(SignalStorag()),&loop,SLOT(quit()));
    QObject::connect(reply,SIGNAL(uploadProgress(qint64,qint64)),this,SLOT(SlotVievDownload(qint64,qint64)));
    QObject::connect(reply,SIGNAL(error(QNetworkReply::NetworkError)),this,SLOT(SlotErrorDownload(QNetworkReply::NetworkError)));

    //void   downloadProgress ( qint64 bytesReceived, qint64 bytesTotal )

    loop.exec();

    buf->clear();
    delete buf;
    emit doCleaning();


  //  emit SignalLogView("Метка GetFile 1_5 ");
    return true;
}



















