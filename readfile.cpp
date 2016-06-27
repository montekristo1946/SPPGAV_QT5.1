#include "readfile.h"

Readfile::Readfile(QObject *parent) :
    QObject(parent)
{

    inPass= "Ckjys blen yf ctdth";
    //qDebug()<<"конструктор Readfile";

    //задаем параметры settings, для чтения каталога проги в реестре
    settingsReestr = new QSettings("HKEY_CURRENT_USER\\Software\\SPP Gav\\Settings",
                                   QSettings::NativeFormat,this);


    settings = new QSettings(settingsReestr->value("Catalog","C:/spp").toString()+"/setting.ini",//задаем каталог в котором лежит исполняемый файл
                             QSettings::IniFormat,this);

    Crypt = new MyCrypto();


    IDD = ReadSetting("Keyy05");
    inTimePodshet =ReadSetting("Keyu06");
    ImyFile = settingsReestr->value("Catalog","C:/spp").toString();
}


bool Readfile::VriteSetting(QString parametr, QString znachenie,QString NomerVideo)
{
    // qDebug()<< parametr <<" - "<<znachenie<< " "<<NomerVideo;
    //qDebug()<< parametr+NomerVideo <<" "<<parametr+NomerVideo<<" "<<znachenie<< " - "<<myCrypt(znachenie,1);
    // settings->setValue(myCrypt(parametr+NomerVideo,1),myCrypt(znachenie,1));//записал настройки в реестр
    //qDebug()<<ReadSetting(parametr,NomerVideo);

    //settings->setValue(parametr+NomerVideo,myCrypt(znachenie,1));
    //settings->setValue(myCrypt(parametr+NomerVideo),myCrypt(znachenie,1));
    //settings->setValue(Crypt->Crypt(parametr+NomerVideo),Crypt->Crypt(znachenie));
    settings->setValue(myCrypt(parametr+NomerVideo),Crypt->Crypt(znachenie));


}

QString Readfile::ReadSetting(QString parametr,QString NomerVideo)
{

    // QString tmp1 = settings->value(myCrypt(parametr+NomerVideo,1),"0").toString();
    //"0"- это параметр по умолчанию settings (если не смог найти)
    //return myCrypt(tmp,0);

    // qDebug()<< NomerVideo <<" "<<parametr<< " "<<myCrypt(parametr+NomerVideo,1)<<" - "<<tmp1;
    //QString tmp = myCrypt(settings->value(parametr+NomerVideo,"0").toString(),0);

   // return myCrypt(settings->value(myCrypt(parametr+NomerVideo),"0").toString(),0);
    return Crypt->DeCrypt(settings->value(myCrypt(parametr+NomerVideo),"0").toString());
}

void Readfile::PerviyStartParametr()
{
    /* PasswordFtp    %Jktcz18783461
        LoginFtp    %gorin
        Port    %21
        UrlFtp    %ftp://ftp1.gloria-jeans.ru/Share/expotVatkom/
        IDD    %0001212
        Camera    %D:\opencv\5.avi
        inNomerProhoda 			%1
        inTimePodshet    %6
        InstantaneousContrast    %8
        MaxKrug    %15000
        MinKrug    %1000
        line1    %120
        line4    %40
        line5    %200
        Livepeople    %4
        PorogPerekritiy    %10
        KrugCheloveka    %50
        RastoynieMegduChelami    %70
        porogSetup    %140
        BackgroundUpdate    %500
        timeONRunH    %10
        timeONRunM    %00
        timeOFFRunH    %22
        timeOFFRunM    %00
        OnMainWindows    %1
        */

    settingsReestr->setValue("Catalog","C:\\spp");//записать каталог по умолчанию!

    for (int i(1);i<7;i++)
    {
        VriteSetting("Keyq01","Jktcz18783461",QString::number(i)); //FTP Парль -PasswordFtp
        VriteSetting("Keyw02","gorin",QString::number(i));         //FTP логин -LoginFtp
        VriteSetting("Keye03","21",QString::number(i)); //FTP порт -Port
        VriteSetting("Keyr04","ftp://ftp1.gloria-jeans.ru/Share/expotVatkom/",QString::number(i)); //FTP  -UrlFtp
        VriteSetting("Keyt23","on",QString::number(i)); //FTP отправка отчета на фТП

        VriteSetting("Keyy05","0001212",QString::number(i)); //IDD (7 знаков)
        VriteSetting("Keyu06","900",QString::number(i)); //Время подсчета,  через равные интервлы времени записываем в файл -inTimePodshet
        VriteSetting("Keyi07","15000",QString::number(i)); //максимльный круг обнаружения -MaxKrug
        VriteSetting("Keyo08","1000",QString::number(i)); //минимальный круг обнаружения -MinKrug
        VriteSetting("Keyp09","120",QString::number(i)); //Центральная линия пересечения -line1
        VriteSetting("Keya10","40",QString::number(i)); //Верхняя линия пересченеия  -line4
        VriteSetting("Keys11","200",QString::number(i)); //Нижняя линия пересечения  -line4
        VriteSetting("Keyd12","4",QString::number(i)); //Колличество кадров жизнь обьекта -Livepeople
        VriteSetting("Keyf13","10",QString::number(i)); //Порог перекрытия обьектов -PorogPerekritiy
        VriteSetting("Keyg14","50",QString::number(i)); //Круг человека -KrugCheloveka
        VriteSetting("Keyh15","70",QString::number(i)); //Фиксированое расстояние между обьектами которые движутся -RastoynieMegduChelami
        VriteSetting("Keyj16","140",QString::number(i)); //Порог Детекции между фоном и новой картинкой -porogSetup
        VriteSetting("Keyk17","500",QString::number(i)); //Кол Кадров,после которых обновится фон -BackgroundUpdate
        VriteSetting("Keyl25","8",QString::number(i)); //Мгновенная контрастность InstantaneousContrast
        VriteSetting("Keye35","on",QString::number(i)); //Зеркалить видео
        VriteSetting("Keyr36","320",QString::number(i)); //ширина видео
        VriteSetting("Keyt37","240",QString::number(i)); //высота видео

        //включение и выключения подсчета по расписанию
        VriteSetting("Keyz18","10",QString::number(i)); //-timeONRunH
        VriteSetting("Keyx19","00",QString::number(i)); //-timeONRunM
        VriteSetting("Keyc20","22",QString::number(i)); //-timeOFFRunH
        VriteSetting("Keyv21","00",QString::number(i)); //-timeOFFRunM



        VriteSetting("Keym24","off",QString::number(i)); // Включен поток или нет (на случай перезагрузки)

        VriteSetting("Keyq26","on",QString::number(i));//запись видео
        VriteSetting("Keyz27","12",QString::number(i)); //-время записи и timeON час
        VriteSetting("Keyx28","00",QString::number(i)); //timeON мин
        VriteSetting("Keyc29","21",QString::number(i)); //-timeOFF час
        VriteSetting("Keyv30","00",QString::number(i)); //-timeOFFR мин

        //камеры
        //VriteSetting("Keyb22","http://admin:admin@192.168.2.5/video/mjpg.cgi?.mjpg",QString::number(i)); //-Cam1
        VriteSetting("Keyb22","Login",QString::number(i)); //-Cam1
        VriteSetting("Keyn31","Pass",QString::number(i)); //-Cam1
        VriteSetting("Keym32","IP",QString::number(i)); //-Cam1
        VriteSetting("Keyq33","Port",QString::number(i)); //-Cam1
        VriteSetting("Keyw34","url",QString::number(i)); //-Cam1
    }
}

bool Readfile::WriteReports(QString Nomerprohoda,QString InPeople,QString OutPeople)
{
    //Формируем название файла
    // 0001212_20141001_000000.txt
    //emit SignalLogView("Запустился WriteReports, Класс Readfile (Тест удали сообщение)");

   // QDate DateNowD;

    //QString DateNowS;
  // QString  IDD;

   QDate DateNowD=QDate::currentDate();



    QString DateNowS = DateNowD.toString("yyyy")+DateNowD.toString("MM")+DateNowD.toString("dd");


    //qDebug()<<IDD;



    QFile file(ImyFile+"\\reports\\"+IDD+"_"+DateNowS+"_000000.txt");

    //формируем содержимое файла
    //1;24.09.2014 17:35:54;900;0;1;2;0

    // QString Nomerprohoda = "1";
    QTime TimeNow = QTime::currentTime();
    // QString InPeople = "12";
    //QString OutPeople= "19";
    QString R = ";";
    // QString F = ".";
    // QString L = ":";

    QString StrokaWriteFile;
    /*StrokaWriteFile = Nomerprohoda+R+QString::number(DateNowD.day())+F+QString::number(DateNowD.month())+F+
            QString::number(DateNowD.year())+" "+QString::number(TimeNow.hour())+L+QString::number(TimeNow.minute())+L+
            QString::number(TimeNow.second())+R+inTimePodshet+R+InPeople+R+OutPeople+R+"2;0\n";
*/

    /*Округляем до кратного заданной минуты 12:13 -> 12:15 (При inTimePodshet == 900)
     * алгоритм работы перевел в милисикунды/inTimePodshet*inTimePodshet- при int потеряется дробная часть, что приведет к окугленюи ближайшего меньшего
     */
    int setTMP =(((TimeNow.minute()*60)/inTimePodshet.toInt()*inTimePodshet.toInt())/60);
    TimeNow.setHMS(TimeNow.hour(),setTMP,0);


    StrokaWriteFile = Nomerprohoda+R+DateNowD.toString("dd.MM.yyyy")+" "+TimeNow.toString("HH:mm:ss")
            +R+inTimePodshet+R+InPeople+R+OutPeople+R+"2;0\n";



    //открываем файл и заполняем
    // if (file.exists())
    // {
    if(file.open(QIODevice::Append| QIODevice::Text  ))
    {

        QTextStream out(&file);
        out<<StrokaWriteFile;

        file.close();
        // emit SignalLogView("Отработал WriteReports, Класс Readfile (Тест удали сообщение)");
        return true;
    }
    else
    {
        emit SignalLogView ("Несмог открыть файл (Reports) "+ImyFile);
        return false;

    }
    // }

}

bool Readfile::WriteDebugLOG(QString tmp)
{
    QFile file("LOG.txt");
    if(file.open(QIODevice::Append| QIODevice::Text  ))
    {

        QTextStream out(&file);
        out<<tmp;

        file.close();
        return true;
    }
    else
    {
        emit SignalLogView ("Несмог открыть файл LOG.txt" );
        return false;

    }
}

Readfile::~Readfile()
{
    //qDebug()<<"деструктор Readfile";

    Crypt->deleteLater();
    settingsReestr->deleteLater();
    settings->deleteLater();
}

QString Readfile::myCrypt(QString inText, int mode)
{
   if (inText.isEmpty())return "NULL";
    QByteArray in;
        in.append(inText);

        QByteArray res;

        QByteArray pass;
        pass.append(inPass);

        for (int i = 0; i < in.size(); i++)
        {
            res.append(in[i] ^ pass[i % pass.length()]);
        }

    return res;
}












