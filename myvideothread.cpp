#include "myvideothread.h"

MyVideoThread::MyVideoThread(QObject *parent, int NomerPotokat) :
    QThread(parent)

{


    moveToThread(this);
    NomerPotoka = NomerPotokat;
    StorogVideoPotok.OnPotok = false;

    //  qDebug()<<"Поток Создан = "<<NomerPotoka ;

    // emit SignalLogView("Создан поток камеры № "+NomerPotoka);

    // capture = new VideoCapture;
     record = new VideoWriter;

    MyReadfile = new Readfile();
    TimerStorag.start(60000);//сторожевой таймер на случай зависаиня!

}

void MyVideoThread::run()
{
    emit SignalLogView("Создан поток камеры № "+QString::number(NomerPotoka));
    //  processFrameAndUpdateGui();
    qDebug()<<"MyVideoThread::run()!!!" ;
    if (!StorogVideoPotok.OnPotok)StorogVideoPotok.OnPotok =true;
    initPainter();// инициализируем переменные!
    connectTo(ConnectIP,ConnectPort,ConnectUrl,ConnectLogin,ConnectPass);

    connect(&TimerStorag, SIGNAL(timeout()), this, SLOT(SlotStorag()));


    exec();
}

void MyVideoThread::initPainter()//инициализипуем переменные
{

    //emit SignalLogView("Запустился initPainter, Класс MyVideoThread, поток "+ QString::number(NomerPotoka)+ " (Тест удали сообщение)");
    //задаем параметры settings, для чтения каталога проги в реестре
    settingsReestr = new QSettings("HKEY_CURRENT_USER\\Software\\SPP Gav\\Settings",
                                   QSettings::NativeFormat,this);


    MaxKrug = MyReadfile->ReadSetting("Keyi07",QString::number(NomerPotoka)).toInt();// рамер мах круга
    MinKrug = MyReadfile->ReadSetting("Keyo08",QString::number(NomerPotoka)).toInt();// рамер минимального круга
    line1 = MyReadfile->ReadSetting("Keyp09",QString::number(NomerPotoka)).toInt();//Центральная линия пересечения -line1
    line4 = MyReadfile->ReadSetting("Keya10",QString::number(NomerPotoka)).toInt();//Верхняя линия пересченеия  -line4
    line5 = MyReadfile->ReadSetting("Keys11",QString::number(NomerPotoka)).toInt();//Нижняя линия пересечения  -line4
    Livepeople = MyReadfile->ReadSetting("Keyd12",QString::number(NomerPotoka)).toInt();;//Колличество кадров жизнь обьекта -Livepeople
    PorogPerekritiy = MyReadfile->ReadSetting("Keyf13",QString::number(NomerPotoka)).toInt(); // допустимая величина наложение кругов
    KrugCheloveka = MyReadfile->ReadSetting("Keyg14",QString::number(NomerPotoka)).toInt();//постоянная велечена круга человека
    RastoynieMegduChelami = MyReadfile->ReadSetting("Keyh15",QString::number(NomerPotoka)).toInt();// фиксированое расстояние между обьектами которые движутся!
    porogSetup = MyReadfile->ReadSetting("Keyj16",QString::number(NomerPotoka)).toInt(); //порог чуствительности
    BackgroundUpdate = MyReadfile->ReadSetting("Keyk17",QString::number(NomerPotoka)).toInt();//частота обновления фона 5минут /24 кадра - 7200
    PutCamera = MyReadfile->ReadSetting("Keyb22",QString::number(NomerPotoka));
    InstantaneousContrast= MyReadfile->ReadSetting("Keyl25",QString::number(NomerPotoka)).toInt();//мгновенная контрастность (8)

/*

    // PutCamera = "d:\\opencv\\5-2.avi";

    MaxKrug = 15000;// рамер мах круга
    MinKrug = 1000;// рамер минимального круга
    line1 = 120;//Центральная линия пересечения -line1
    line4 = 40;//Верхняя линия пересченеия  -line4
    line5 = 200;//Нижняя линия пересечения  -line4
    Livepeople = 4;//Колличество кадров жизнь обьекта -Livepeople
    PorogPerekritiy = 10; // допустимая величина наложение кругов
    KrugCheloveka = 50;//постоянная велечена круга человека
    RastoynieMegduChelami = 70;// фиксированое расстояние между обьектами которые движутся!
    porogSetup = 140; //порог чуствительности
    BackgroundUpdate = 500;//частота обновления фона 5минут /24 кадра - 7200
    PutCamera = "d:\\opencv\\5-3.avi";
    InstantaneousContrast = 8;

  qDebug()<<"MaxKrug "<<MaxKrug;
   qDebug()<<"MinKrug "<<MinKrug;
qDebug()<<"Livepeople "<<Livepeople;
qDebug()<<"PorogPerekritiy "<<PorogPerekritiy;
   qDebug()<<"KrugCheloveka "<<KrugCheloveka;
       qDebug()<<"RastoynieMegduChelami "<<RastoynieMegduChelami;
          qDebug()<<"porogSetup "<<porogSetup;
             qDebug()<<"BackgroundUpdate "<<BackgroundUpdate;
                qDebug()<<"PutCamera "<<PutCamera;
qDebug()<<"InstantaneousContrast "<<InstantaneousContrast;

*/

    line2 = 0;//линия пересечени
    line3 = 0;//линия пересечени
    InPeple=0;
    OutPeple=0;
    StorogVideoPotok.FirstFrame=true;
    StorogVideoPotok.outPeople = 0;
    StorogVideoPotok.inPeople = 0;
    StorogVideoPotok.SendImege = false;
    StorogVideoPotok.OnPotok = false;

    line2 = line1 + 20;//линия пересечени
    line3 = line1 - 20;//линия пересечени


    //   PutCamera = "http://admin:admin@192.168.2.5/video/mjpg.cgi?.mjpg";
    /*
 *  CvSize size = cvSize(320, 240);// запись потока подготовка
 *  VideoWriter record("start1.avi", CV_FOURCC('D','I','V','X'), 10, size, true);
 *  if (record1.isOpened()) {record1.write(mat);}// запись потока
 *
 */

     m_socket=0;
     m_boundary="";
     m_firstBlock=true;
     m_dataBlock="";
     //m_autoReconnect=true;
     m_autoReconnect=false;



    if(MyReadfile->ReadSetting("Keye35","1")=="on")//зеркалить
     m_flipImage=true;
    else m_flipImage=false;

     m_pollMode=false;
     m_pollFps=10;
     FlagStorag=false;

    ConnectLogin = MyReadfile->ReadSetting("Keyb22",QString::number(NomerPotoka));
    ConnectPass = MyReadfile->ReadSetting("Keyn31",QString::number(NomerPotoka));
     ConnectIP = MyReadfile->ReadSetting("Keym32",QString::number(NomerPotoka));
     ConnectPort=MyReadfile->ReadSetting("Keyq33",QString::number(NomerPotoka)).toInt();
     ConnectUrl= MyReadfile->ReadSetting("Keyw34",QString::number(NomerPotoka));
/*
qDebug()<<ConnectIP;
qDebug()<<QString::number(ConnectPort);
qDebug()<<"ConnectLogin "<<ConnectLogin;
qDebug()<<"ConnectPass "<<ConnectPass;
qDebug()<<ConnectUrl;

     emit SignalLogView(ConnectIP);
     emit SignalLogView("login " +ConnectLogin);
     emit SignalLogView("pass " +ConnectPass);
     emit SignalLogView(ConnectUrl);
     emit SignalLogView(QString::number(ConnectPort));
*/
      WidthFrame = MyReadfile->ReadSetting("Keyr36","1").toInt();//ширина видео
      HeightFrame = MyReadfile->ReadSetting("Keyt37","1").toInt();//высота видео
      size = cvSize(WidthFrame, HeightFrame);
      m_autoResize.setWidth(WidthFrame);
      m_autoResize.setHeight(HeightFrame);


}

MyVideoThread::~MyVideoThread()
{

    //emit SignalLogView(" Разрушен поток камеры № " +QString::number(NomerPotoka) );
  //  this->msleep(10);

   // qDebug()<<"поток разрушился MyVideoThread" ;
   // StorogVideoPotok.OnPotok =false;
   // delete MyReadfile;
   // delete capture;
    delete record;

    //delete m;
    TimerStorag.deleteLater();

    MyReadfile->deleteLater();
    this->deleteLater();


}

void MyVideoThread::FunkVichislenie()
{

    porog = porogSetup;//выставим в исходную позицию порог контрастности

    image = frame.clone();

    // - обработка изображения
    if (BackgroundUpdatetmp <= 0 && FStrukturaKrugntKollPeople() == 0)
    {
        image = frame.clone();
        //image.copyTo( frame );
        TrainBackground(&image);
        BackgroundUpdatetmp = BackgroundUpdate;
        qDebug()<<"обновил фон";
    }
    if (BackgroundUpdatetmp <= 0)//если время обновлять, но обновление не прошло, занчит добавляем яркость картинки!
    {
        porog += 40;
    }


   do{

        image = frame.clone();
        MotionDetection(&image, porog);// отделяет фон от движущихся предметов

      erode(image, image, kern, Point(-1, -1), 1);//Размывает изображение с использованием специального структурного элемента.

        cvtColor(image, image, CV_BGR2GRAY);//преобразуем в градиент серого
        threshold(image, fore, 128, 255, CV_THRESH_BINARY);//конвертация в 8 битное изображение

        porog += 30.0;
        // qDebug()<<"цикл ";


   } while (contrastFilter(&image)>InstantaneousContrast);//если слишком много найдено элементов то в цикле увеличиваем порог чуствительности

/*
    QImage qimage_1 =  QImage ((uchar*)image.data, image.cols, image.rows, image.step,
                      QImage::Format_Indexed8);
    emit MySendDataVideFrame(qimage_1);// сигнал видео
    */


    findContours(fore, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);//находим контуры
   cv::drawContours(frame, contours, -1, cv::Scalar(0, 0, 255), 1);//рисуем контуры


    for (int i = 0; i < contours.size(); i++)//проходим по содержимому контурам
    {

        if (i>M_E_S)//избежать ошибки выхода за пределы структуры!!!!
        {
            qDebug()<< "ERROR 13 - M_E_S" ;

            return ;

        }



        if (fabs(contourArea(contours[i])) > MinKrug && fabs(contourArea(contours[i])) < MaxKrug)//отсортируем большие и малые круги
        {

            Point2f center;
            float radius;
            minEnclosingCircle(contours[i], center, radius);

            StrukturaKrug[FStrukturaKrugntKoll()].center = center;
            StrukturaKrug[FStrukturaKrugntKoll()].radius = KrugCheloveka;//постоянная велечена круга человека
            StrukturaKrug[FStrukturaKrugntKoll()].risovat = true;
            StrukturaKrug[FStrukturaKrugntKoll()].zapolnen = true;

            //cout << area << "   x " << center.x << "  y " << center.y << "   radius " << radius << endl;//удали
        }
    }

    FunkObedinenie();
    FunkPodscheta();
    FunkPodschetPeopleObnuleniy();

    for (int i = 0; i < FStrukturaKrugntKoll(); i++) //нарисуем круги большие круги
    {
        if (StrukturaKrug[i].risovat) //
            circle(frame, StrukturaKrug[i].center, StrukturaKrug[i].radius, cvScalar(0, 0, 255));

    }
    for (int i = 0; i < FStrukturaKrugntKollPeople(); i++) //нарисуем круги центры больших кругов
    {
        if (StrukturaPodschetPeople[i].risovat && StrukturaPodschetPeople[i].line2 == false)
            circle(frame, StrukturaPodschetPeople[i].center, 10, cvScalar(255, 0, 0));
        if (StrukturaPodschetPeople[i].risovat && StrukturaPodschetPeople[i].line2 == true)
            circle(frame, StrukturaPodschetPeople[i].center, 10, cvScalar(0, 255, 0));
/*
        std::ostringstream ost;
        ost << i;
        std::string str1 = ost.str();
        */
        int fontFace = CV_FONT_HERSHEY_DUPLEX;
        double fontScale = 0.5;
        int thickness = 0.5;
        //напишим номер обьекта в центре маленькой окружности
        putText(frame, QString::number(i).toStdString(), StrukturaPodschetPeople[i].center, fontFace, fontScale, CV_RGB(0, 255, 0), thickness, 1);

    }

    //рисуем линии
    CvPoint b;
    b.x = 0;
    b.y = line1;
    CvPoint b1;
    b1.x = frame.size().width;
    b1.y = line1;
    line(frame, b, b1, CV_RGB(0, 0, 255), 1);
    b.y = line2;
    b1.y = line2;
    line(frame, b, b1, CV_RGB(0, 0, 255), 1);
    b.y = line3;
    b1.y = line3;
    line(frame, b, b1, CV_RGB(0, 0, 255), 1);

    b.y = line4;
    b1.y = line4;
    line(frame, b, b1, CV_RGB(0, 255, 0), 1);

    b.y = line5;
    b1.y = line5;
    line(frame, b, b1, CV_RGB(0, 255, 0), 1);

    //вывести текст-------------------


    CvPoint c;

    c.x = 20;
    c.y = 30;

    CvPoint c1;
    c1.x = 20;
    c1.y = m_autoResize.height()-30;


    putText(frame, QString::number(InPeple).toStdString(), c, CV_FONT_HERSHEY_DUPLEX, 1, CV_RGB(0, 255, 0), 0.5, 1);
    putText(frame, QString::number(OutPeple).toStdString(), c1, CV_FONT_HERSHEY_DUPLEX, 1, CV_RGB(0, 255, 0), 0.5, 1);

}

void MyVideoThread::TrainBackground(Mat* image)
{

    //QVector<float> m[image->size().height*image->size().width * 3];
    //QByteArray m[image->size().height*image->size().width * 3];
    double alpha = 0.8;//коэфиценты веса
    double beta = 0.2;

    addWeighted(cacheFrame, alpha, *image, beta, 0.0, cacheFrame);//сливаем фоновый рисунок и новый полученный
/*
    int i, j;
    int j1;
   // QChar * ptr;

    uchar* ptr;
    ptr = (uchar*)(cacheFrame.data);
   // ptr = (QChar*)(cacheFrame.data);


    for (i = 0; i<cacheFrame.size().height; i++)
        for (j = 0; j<cacheFrame.size().width; j++)
            for (j1 = 0; j1<3; j1++)
            {
                m[(i*cacheFrame.size().width + j) * 3 + j1] = 0;



              m[(i*cacheFrame.size().width + j) * 3 + j1] = ptr[j * 3 + i*cacheFrame.step + j1];

              //  m[(i*cacheFrame.size().width + j) * 3 + j1] = m[(i*cacheFrame.size().width + j) * 3 + j1];
            }

*/

}


void MyVideoThread::MotionDetection(Mat *image, float porog)
{



    int i, j;
    float k = 0;
    int  j1;
    uchar* ptr;
    ptr = (uchar*)(image->data);

    uchar* ptr_2;
    ptr_2 = (uchar*)(cacheFrame.data);

    for (i = 0; i<image->size().height; i++)
        for (j = 0; j<image->size().width; j++)
        {
            k = 0;
            for (j1 = 0; j1<3; j1++)
               // k += abs(m[(i*image->size().width + j) * 3 + j1] - ptr[j * 3 + i*image->step + j1]);
               // k += abs(m->at((i*image->size().width + j) * 3 + j1) - ptr[j * 3 + i*image->step + j1]);
               k += abs(ptr_2[j * 3 + i*image->step + j1] - ptr[j * 3 + i*image->step + j1]);
            if (k <= porog) //заливает фон
            {
                for (j1 = 0; j1 < 3; j1++)
                {
                    if (j1 == 0) ptr[j * 3 + i*image->step + j1] = 0;
                    else ptr[j * 3 + i*image->step + j1] = 0;
                }
            }
            else//заливает движущие обьекты
            {
                for (j1 = 0; j1 < 3; j1++)
                {
                    if (j1 == 0) ptr[j * 3 + i*image->step + j1] = 255;
                    else ptr[j * 3 + i*image->step + j1] = 255;
                }
            }


        }

}

int MyVideoThread::contrastFilter(Mat* in)
{

    int imageRows = in->size().height;
    int imageCols = in->size().width;

    int lAB = 0;
    unsigned char valueB = 0;
    unsigned char valueG = 0;
    unsigned char valueR = 0;


    //Находим яркость всех пикселей
    for (int j = 0; j < in->rows*in->cols; j = j + 3)
    {
        valueB = in->data[j];
        valueG = in->data[j + 1];
        valueR = in->data[j + 2];

        lAB += (int)(valueR * 0.299 + valueG * 0.587 + valueB * 0.114);
    }

    //средняя яркость всех пикселей
    lAB /= imageRows * imageCols;

    // qDebug()<<lAB;
    /* if (lAB>40)emit SignalLogView(" Камера - "+QString::number(NomerPotoka)+
                                 ": Заполенение выбранными обьектами более " +QString::number(lAB) );

                                 */
    return lAB;

}

int MyVideoThread::FStrukturaKrugntKoll()
{
    for (int i = 0; i < M_E_S; i++)
    {
        if (StrukturaKrug[i].zapolnen == false)
            return i;
    }
    return 0;
}

int MyVideoThread::FStrukturaKrugntKollPeople()
{
    for (int i = 0; i < M_E_S; i++)
    {
        if (StrukturaPodschetPeople[i].zapolnen == false)
            return i;
    }
    return 0;
}

void MyVideoThread::FStrukturaObnulenie()
{
    int j = FStrukturaKrugntKoll();
    for (int i = 0; i < j; i++)
    {
        StrukturaKrug[i].center.x = 0;
        StrukturaKrug[i].center.y = 0;
        StrukturaKrug[i].radius = 0.0;
        StrukturaKrug[i].risovat = false;
        StrukturaKrug[i].zapolnen = false;

    }
}

void MyVideoThread::FunkObedinenie()
{
    for (int i = 0; i != FStrukturaKrugntKoll(); i++)
    {

        for (int j = i + 1; j != FStrukturaKrugntKoll(); j++)
        {
            if (StrukturaKrug[i].risovat && StrukturaKrug[j].risovat)
            {
                //if (abs(a1-a2) <= r1+r2 && abs(b1-b2) <= r1+r2){
                //if (sqrt(sqr(x1-x2)+sqr(y1-y2))>r1+r2) or	(sqrt(sqr(x1 - x2) + sqr(y1 - y2))<r1 + r2) then не пересекаются

                if (sqrt((abs(StrukturaKrug[i].center.x - StrukturaKrug[j].center.x))*(abs(StrukturaKrug[i].center.x - StrukturaKrug[j].center.x)) +
                         (abs(StrukturaKrug[i].center.y - StrukturaKrug[j].center.y))*(abs(StrukturaKrug[i].center.y - StrukturaKrug[j].center.y)))
                        <= StrukturaKrug[i].radius + StrukturaKrug[j].radius - PorogPerekritiy
                        )

                {
                    //cout << "peresechenie obedinil krugi " << i <<" " << j << endl;
                    CvPoint C0;//центр нового квадрата
                    C0.x = (StrukturaKrug[i].center.x + StrukturaKrug[j].center.x) / 2;
                    C0.y = (StrukturaKrug[i].center.y + StrukturaKrug[j].center.y) / 2;
                  /*
                    double radius;
                    if (StrukturaKrug[i].radius >= StrukturaKrug[j].radius)//выявляю больший круг
                    {
                        radius = StrukturaKrug[i].radius;
                    }
                    else
                    {
                        radius = StrukturaKrug[j].radius;
                    }*/

                    int s = FStrukturaKrugntKoll();
                    StrukturaKrug[s].center.x = C0.x;
                    StrukturaKrug[s].center.y = C0.y;
                    StrukturaKrug[s].radius = KrugCheloveka;//постоянная велечена круга человека
                    //StrukturaKrug[s].radius = radius;
                    StrukturaKrug[s].risovat = true;
                    StrukturaKrug[s].zapolnen = true;
                    StrukturaKrug[j].risovat = false;
                    StrukturaKrug[i].risovat = false;
                }
            }
        }
    }
}


void MyVideoThread::FunkPodscheta()
{
    bool dobavitPipla = false;
    bool flag = true;

    for (int i = 0; i != FStrukturaKrugntKoll(); i++)
    {
        if (FStrukturaKrugntKollPeople() == 0 && StrukturaKrug[i].risovat)
        {
            StrukturaPodschetPeople[0].center = StrukturaKrug[i].center;
            StrukturaPodschetPeople[0].radius = StrukturaKrug[i].radius;
            StrukturaPodschetPeople[0].TimeLive = Livepeople;
            StrukturaPodschetPeople[0].zapolnen = true;
            StrukturaPodschetPeople[0].risovat = true;
            dobavitPipla = false;
            break;
        }

        flag = true;
        for (int j = 0; j != FStrukturaKrugntKollPeople(); j++)
        {
            if (StrukturaKrug[i].risovat && StrukturaPodschetPeople[j].risovat)
            {
                /*
                cout << "rastoynie i " << i << " and " << " j " << j << " " <<
                sqrt((abs(StrukturaKrug[i].center.x - StrukturaPodschetPeople[j].center.x))*(abs(StrukturaKrug[i].center.x - StrukturaPodschetPeople[j].center.x)) +
                (abs(StrukturaKrug[i].center.y - StrukturaPodschetPeople[j].center.y))*(abs(StrukturaKrug[i].center.y - StrukturaPodschetPeople[j].center.y)))
                << "   vremy gizni J-go " << StrukturaPodschetPeople[j].TimeLive << endl;
                */

                if (sqrt((abs(StrukturaKrug[i].center.x - StrukturaPodschetPeople[j].center.x))*(abs(StrukturaKrug[i].center.x - StrukturaPodschetPeople[j].center.x)) +
                         (abs(StrukturaKrug[i].center.y - StrukturaPodschetPeople[j].center.y))*(abs(StrukturaKrug[i].center.y - StrukturaPodschetPeople[j].center.y)))
                        <= RastoynieMegduChelami)//50 фиксированое расстояние между обьектами!
                {
                    ///здесь производим анализ пересечения линий
                    //	cout << " y J = " << StrukturaPodschetPeople[j].center.y << " " << StrukturaPodschetPeople[j].line1
                    //	<< " y I = " << StrukturaKrug[i].center.y << endl;

                    if (StrukturaKrug[i].center.y > StrukturaPodschetPeople[j].center.y&& StrukturaKrug[i].center.y >= line5  && StrukturaPodschetPeople[j].center.y<line5)
                    {
                        StrukturaPodschetPeople[j].line1 = false;
                        StrukturaPodschetPeople[j].line2 = true;
                    }
                    if (StrukturaKrug[i].center.y < StrukturaPodschetPeople[j].center.y&& StrukturaKrug[i].center.y <= line5 && StrukturaPodschetPeople[j].center.y>line5)
                    {
                        StrukturaPodschetPeople[j].line1 = false;
                        StrukturaPodschetPeople[j].line2 = true;

                    }



                    if (StrukturaKrug[i].center.y > StrukturaPodschetPeople[j].center.y&& StrukturaKrug[i].center.y >= line1 &&
                            StrukturaPodschetPeople[j].line1 == false && StrukturaPodschetPeople[j].center.y<line1)
                    {
                        StrukturaPodschetPeople[j].line1 = true;
                        StrukturaPodschetPeople[j].line2 = false;
                        OutPeple++;
                        StorogVideoPotok.outPeople++;
                    }
                    if (StrukturaKrug[i].center.y > StrukturaPodschetPeople[j].center.y&& StrukturaKrug[i].center.y >= line2 &&
                            StrukturaPodschetPeople[j].line1 == false && StrukturaPodschetPeople[j].center.y<line2)
                    {
                        StrukturaPodschetPeople[j].line1 = true;
                        StrukturaPodschetPeople[j].line2 = false;
                        OutPeple++;
                        StorogVideoPotok.outPeople++;
                    }
                    if (StrukturaKrug[i].center.y > StrukturaPodschetPeople[j].center.y&& StrukturaKrug[i].center.y >= line3 &&
                            StrukturaPodschetPeople[j].line1 == false && StrukturaPodschetPeople[j].center.y<line3)
                    {
                        StrukturaPodschetPeople[j].line1 = true;
                        StrukturaPodschetPeople[j].line2 = false;
                        OutPeple++;
                        StorogVideoPotok.outPeople++;
                    }




                    if (StrukturaKrug[i].center.y < StrukturaPodschetPeople[j].center.y&& StrukturaKrug[i].center.y <= line4 && StrukturaPodschetPeople[j].center.y>line4)
                    {
                        StrukturaPodschetPeople[j].line1 = false;
                        StrukturaPodschetPeople[j].line2 = true;

                    }
                    if (StrukturaKrug[i].center.y > StrukturaPodschetPeople[j].center.y&& StrukturaKrug[i].center.y >= line4  && StrukturaPodschetPeople[j].center.y<line4)
                    {
                        StrukturaPodschetPeople[j].line1 = false;
                        StrukturaPodschetPeople[j].line2 = true;
                    }


                    if (StrukturaKrug[i].center.y < StrukturaPodschetPeople[j].center.y&& StrukturaKrug[i].center.y <= line1 &&
                            StrukturaPodschetPeople[j].line1 == false && StrukturaPodschetPeople[j].center.y>line1)
                    {
                        StrukturaPodschetPeople[j].line1 = true;
                        StrukturaPodschetPeople[j].line2 = false;
                        InPeple++;
                        StorogVideoPotok.inPeople++;
                    }
                    if (StrukturaKrug[i].center.y < StrukturaPodschetPeople[j].center.y&& StrukturaKrug[i].center.y <= line2 &&
                            StrukturaPodschetPeople[j].line1 == false && StrukturaPodschetPeople[j].center.y>line2)
                    {
                        StrukturaPodschetPeople[j].line1 = true;
                        StrukturaPodschetPeople[j].line2 = false;
                        InPeple++;
                        StorogVideoPotok.inPeople++;

                    }
                    if (StrukturaKrug[i].center.y < StrukturaPodschetPeople[j].center.y&& StrukturaKrug[i].center.y <= line3 &&
                            StrukturaPodschetPeople[j].line1 == false && StrukturaPodschetPeople[j].center.y>line3

                            )
                    {
                        StrukturaPodschetPeople[j].line1 = true;
                        StrukturaPodschetPeople[j].line2 = false;
                        InPeple++;
                        StorogVideoPotok.inPeople++;
                    }

                    ////------------------
                    StrukturaPodschetPeople[j].center = StrukturaKrug[i].center;
                    StrukturaPodschetPeople[j].radius = StrukturaKrug[i].radius;
                    StrukturaPodschetPeople[j].TimeLive = Livepeople;
                    StrukturaPodschetPeople[j].zapolnen = true;
                    StrukturaPodschetPeople[j].risovat = true;
                    dobavitPipla = false;
                    flag = false;
                }
                else
                {
                    if (flag)
                        dobavitPipla = true;
                }
            }
        }



        if (dobavitPipla  && StrukturaKrug[i].risovat)
        {
            int c = FStrukturaKrugntKollPeople();
            StrukturaPodschetPeople[c].center = StrukturaKrug[i].center;
            StrukturaPodschetPeople[c].radius = StrukturaKrug[i].radius;
            StrukturaPodschetPeople[c].TimeLive = Livepeople;
            StrukturaPodschetPeople[c].zapolnen = true;
            StrukturaPodschetPeople[c].risovat = true;
            dobavitPipla = false;
            //cout << "sozdal Nev people " << c << endl;
        }
    }





}

void MyVideoThread::FunkPodschetPeopleObnuleniy()
{
    int c = FStrukturaKrugntKollPeople();

    for (int i = 0; i != c; i++)//укарачиваем всем время жизни
    {
        if (StrukturaPodschetPeople[i].TimeLive >= 0)
        {
            StrukturaPodschetPeople[i].TimeLive--;
        }
        //	cout << "vremy gizni I " << i<<" " << StrukturaPodschetPeople[i].TimeLive << endl;
    }

    for (int i = 0; i < c; i++)//ищем дублируемы квадраты
    {
        for (int j = i + 1; j < c; j++)
        {
            if (StrukturaPodschetPeople[i].zapolnen && StrukturaPodschetPeople[j].zapolnen)
            {
                if (StrukturaPodschetPeople[i].center.x == StrukturaPodschetPeople[j].center.x &&
                        StrukturaPodschetPeople[i].center.y == StrukturaPodschetPeople[j].center.y)
                {
                    StrukturaPodschetPeople[j].risovat = false;
                    if (StrukturaPodschetPeople[j].line1)
                        StrukturaPodschetPeople[i].line1 = true;
                    if (StrukturaPodschetPeople[j].line2)
                        StrukturaPodschetPeople[i].line2 = true;

                }
            }
        }
    }

    for (int i = 0; i < c; i++)//ищем нулевое время
    {
        if (StrukturaPodschetPeople[i].TimeLive <= 0)
        {
            StrukturaPodschetPeople[i].risovat = false;
        }
    }

    if (c>2)
    {
        for (int i = 0; i < c; i++)//ищем пустые элементы и перемещаем их в начало структуры
        {
            for (int j = i + 1; j < c; j++)
            {
                if (!StrukturaPodschetPeople[i].risovat&& StrukturaPodschetPeople[j].risovat)
                {
                    StrukturaPodschetPeople[i] = StrukturaPodschetPeople[j];
                    StrukturaPodschetPeople[j].risovat = false;
                    i = -1;
                    break;
                }
            }
        }
    }

    for (int i = 0; i < c; i++)//ищем элементы которые нужно удалить/удаляем
    {
        if (!StrukturaPodschetPeople[i].risovat)
        {
            StrukturaPodschetPeople[i].center.x = 0;
            StrukturaPodschetPeople[i].center.y = 0;
            StrukturaPodschetPeople[i].radius = 0;
            StrukturaPodschetPeople[i].TimeLive = 0;//лимит жизни pipla
            StrukturaPodschetPeople[i].zapolnen = false;
            StrukturaPodschetPeople[i].line1 = false;
            StrukturaPodschetPeople[i].line2 = false;
            StrukturaPodschetPeople[i].risovat = false;
            //	cout << "udalil " << i << endl;
        }
    }

}

void MyVideoThread::StoragAlarm()
{
    // qDebug()<<"StoragAlarm() - отработал";
    //StorogVideoPotok.Storag =true;
}

void MyVideoThread::MywaitKey(int tmp)//задержка
{
    if (tmp == -1)//если -1 то нужно обновить время отчета
    {
        TimeNow = QTime::currentTime();
        return;
    }


    QTime TimeNow2 = QTime::currentTime();//вторая точка сравнения

    int sleep = (tmp - TimeNow.msecsTo(TimeNow2));

    if (sleep<0||sleep>200)this->msleep(0);//если задержка оказалась больше промежутка меж кадрами (3 - для обновления кадров)
    else this->msleep(sleep);

    //qDebug()<<sleep;

}

void MyVideoThread::SlotExitThread()
{
    /* if(m_socket)
    {
        m_socket->abort();
        m_socket->disconnectFromHost();
        //m_socket->waitForDisconnected();
        m_socket->deleteLater();
        //delete m_socket;
        m_socket = 0;
    }*/
    //delete MyReadfile;


    disconnect(&TimerStorag, SIGNAL(timeout()), this, SLOT(SlotStorag()));

    emit SignalDisconnect();//завершить захват видео в классе MyVideoThread
    emit SignalLogView("Разрушен поток камеры № " +QString::number(NomerPotoka) );
    this->msleep(50);

    if(m_socket)
    {
        m_socket->abort();
        m_socket->disconnectFromHost();
        //m_socket->waitForDisconnected();
        m_socket->deleteLater();
        //delete m_socket;
        m_socket = 0;
    }
    this->destroyed();
    this->quit();
}

void MyVideoThread::myShow( QImage* qimagetmp)
{
    qimage= *qimagetmp;
    frame = qimage2mat(qimage);

   if (!StorogVideoPotok.OnPotok)StorogVideoPotok.OnPotok =true;//сторожевой таймер

   if (StorogVideoPotok.FirstFrame)
    {

        frame.copyTo( cacheFrame );//задаем первоночальный фон
        BackgroundUpdatetmp = -1;

        //иниализация переменных
       // m = new float[frame.size().height*frame.size().width * 3];

        fore.create(frame.size().width, frame.size().height, IPL_DEPTH_8U); // создаем черно-белый "Mat"
        kern = getStructuringElement(MORPH_ELLIPSE, Size(3, 3), Point(-1, -1));// маска размытия 3,3 рамер матрицы рамытия
        StorogVideoPotok.FirstFrame=false;

    }

    porog = porogSetup;


     //здесь вычисления!!!!! людей
    FunkVichislenie();
    FStrukturaObnulenie();
    BackgroundUpdatetmp--;

     if(StorogVideoPotok.WriteVideo)//если включена запись видео
            {
                if(!record->isOpened())//если не создан файл
                {
                    emit SignalLogView("Начало записи видео с камеры № "+QString::number(NomerPotoka));
                    QDate tmpdate =QDate::currentDate();
                    QTime tmpTime = QTime::currentTime();
                    QString tmp = settingsReestr->value("Catalog","0").toString()+"\\video\\"+tmpdate.toString("dd.MM.yyyy")+"_"
                            +tmpTime.toString("HH.mm.ss")+"_"+QString::number(NomerPotoka)+".avi";
                     record->open(tmp.toStdString(), CV_FOURCC('D','I','V','X'), 10, size, true);
                }
                //qDebug()<<"Включена запись видео- "<<NomerPotoka;
                if (record->isOpened()) {record->write(frame);}// запись потока
            }
            else
            {
               record->release();
            }


    if(StorogVideoPotok.SendImege)//если есть необходимость выводить изображение!!!!
    {
        cvtColor(frame,frame,CV_BGR2RGB);//конверсия для нормальной цветности
        //cvtColor(cacheFrame,cacheFrame,CV_BGR2RGB);
        qimage =  QImage ((uchar*)frame.data, frame.cols, frame.rows, frame.step,
                          QImage::Format_RGB888);

        //emit MySendDataVideFrame(qimage);// сигнал видео
        //QPixmap::fromImage(QImage((unsigned char*) mat.data, mat.cols, mat.rows, QImage::Format_RGB888));
        emit MySendDataVideFrame(QPixmap::fromImage(qimage));// сигнал видео

    }




}

void MyVideoThread::SlotlFirstFrame()//получил первый кадр, для инициализации переменных
{

    StorogVideoPotok.FirstFrame=true;
}

Mat MyVideoThread::qimage2mat(const QImage& qimage)//конвертация QImage to Mat
{
    cv::Mat mat = cv::Mat(qimage.height(), qimage.width(), CV_8UC4, (uchar*)qimage.bits(), qimage.bytesPerLine());
    cv::Mat mat2 = cv::Mat(mat.rows, mat.cols, CV_8UC3 );
    int from_to[] = { 0,0,  1,1,  2,2 };
    cv::mixChannels( &mat, 1, &mat2, 1, from_to, 3 );
    return mat2;
}

/////////////////////////////////////---------------------------


bool MyVideoThread::connectTo(const QString& host, int port, QString url, const QString& user, const QString& pass)
{
    emit SignalFirstFrame();
    if(url.isEmpty())
        url = "/";

    m_host = host;
    m_port = port;
    m_url = url;
    m_user = user;
    m_pass = pass;

   /* if(m_socket)
    {
        m_socket->abort();
        delete m_socket;
        m_socket = 0;
    }*/

    m_socket = new QTcpSocket(this);
    connect(m_socket, SIGNAL(readyRead()),    this,   SLOT(dataReady()));
    connect(m_socket, SIGNAL(disconnected()), this,   SLOT(lostConnection()));
    connect(m_socket, SIGNAL(disconnected()), this, SIGNAL(socketDisconnected()));
    connect(m_socket, SIGNAL(connected()),    this, SIGNAL(socketConnected()));
    connect(m_socket, SIGNAL(connected()),    this,   SLOT(connectionReady()));
    connect(m_socket, SIGNAL(error(QAbstractSocket::SocketError)), this, SIGNAL(socketError(QAbstractSocket::SocketError)));
    connect(m_socket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(lostConnection(QAbstractSocket::SocketError)));

    m_socket->connectToHost(host,port);
    m_socket->setReadBufferSize(1024 * 1024);


    return true;
}

void MyVideoThread::connectionReady()
{
    char data[1024];
    sprintf(data, "GET %s HTTP/1.0\r\n",qPrintable(m_url));
    m_socket->write((const char*)&data,strlen((const char*)data));

    sprintf(data, "Host: %s\r\n",qPrintable(m_host));
    m_socket->write((const char*)&data,strlen((const char*)data));

    if(!m_user.isEmpty() || !m_pass.isEmpty())
    {
        //qDebug() << "Authorizing using username: "<<m_user;
        sprintf(data, "%s:%s",qPrintable(m_user),qPrintable(m_pass));
        QByteArray auth = QByteArray((const char*)&data).toBase64();
        sprintf(data, "Authorization: Basic %s\r\n",auth.constData());
        m_socket->write((const char*)&data,strlen((const char*)data));
    }

    sprintf(data, "\r\n");
    m_socket->write((const char*)&data,strlen((const char*)data));
}

void MyVideoThread::log(const QString& str)
{
    qDebug() << "MyVideoThread::log(): "<<str;
}


void MyVideoThread::lostConnection()
{
    if(m_autoReconnect)
        QTimer::singleShot(1000,this,SLOT(reconnect()));
}

void MyVideoThread::lostConnection(QAbstractSocket::SocketError error)
{
    qDebug() << "MyVideoThread::lostConnection("<<error<<"):" << m_socket->errorString();

    emit SignalLogView("Ошибка соединение с камерой № "+QString::number(NomerPotoka)+" "+m_socket->errorString());

    if(error == QAbstractSocket::ConnectionRefusedError||QAbstractSocket::NetworkError)//тип ошибок: отказ конекта, проблема с сетью
        lostConnection();
}


void MyVideoThread::reconnect()
{
    //log(QString("Attempting to reconnect to http://%1:%2%3").arg(m_host).arg(m_port).arg(m_url));
    qDebug()<<"Реконект!!!";
    m_socket->abort();
    m_socket->disconnectFromHost();
    //delete m_socket;
    m_socket->deleteLater();
    connectTo(m_host,m_port,m_url,m_user,m_pass);

}

void MyVideoThread::dataReady()
{
    QByteArray bytes = m_socket->readAll();
    if(bytes.size() > 0)
    {
        m_dataBlock.append(bytes);
        processBlock();
    }
}

void MyVideoThread::processBlock()
{
    if(m_boundary.isEmpty())
    {
        // still waiting for boundary string defenition, check for content type in data block
        char * ctypeString = 0;
        if(m_dataBlock.contains("Content-Type:"))
        {
            ctypeString = "Content-Type:";
        }
        else
        if(m_dataBlock.contains("content-type:"))
        {
            // allow for buggy servers (some IP cameras - trendnet, I'm looking at you!)
            // sometimes dont use proper case in their headers.
            ctypeString = "content-type:";
        }

        if(ctypeString)
        {
            int ctypeIdx = m_dataBlock.indexOf(ctypeString);
            if(ctypeIdx < 0)
            {
                qDebug() << "Error: Can't find content-type index in data block, exiting.";
                exit();
                return;
            }

            static QString boundaryMarker = "boundary=";
            int boundaryStartIdx = m_dataBlock.indexOf(boundaryMarker,ctypeIdx);
            if(boundaryStartIdx < 0)
            {
                qDebug() << "Error: Can't find boundary index after the first content-type index in data block, exiting:"<<m_dataBlock;
                exit();
                return;
            }

            int eolIdx = m_dataBlock.indexOf("\n",boundaryStartIdx);
            int pos = boundaryStartIdx + boundaryMarker.length();
            m_boundary = m_dataBlock.mid(pos, eolIdx - pos);
            m_boundary.replace("\r","");
// 			qDebug() << "processBlock(): m_boundary:"<<m_boundary<<", pos:"<<pos<<", eolIdx:"<<eolIdx;
        }
    }
    else
    {
        // we have the boundary string defenition, check for the boundary string in the data block.
        // If found, grab the data from the start of the block up to and including the boundary, leaving any data after the boundary in the block.
        // What we then have to process could look:
        // Content-Type.....\r\n(data)--(boundary)

        // If its the first block, we wait for the boundary, but discard it since the first block is the one that contains the server headers
        // like the boundary definition, Server:, Connection:, etc.

        // У нас есть граничную строку Defenition, проверьте границы строки в блоке данных.
                 // Если нашли, возьмите данные из начала блока до и включая границы, оставив никаких данных после границы в блоке.
                 // То, что мы тогда должны обрабатывать может выглядеть:
                 // Content-Type ..... \ т \ п (данные) - (граница)

                 // Если его первого блока, мы ждем границы, но отказаться от него, так как первый блок, который содержит заголовки сервера
                 // Как границы определения, Server :, Подключение :, и т.д.

        int idx = m_dataBlock.indexOf(m_boundary);

        while(idx > 0)
        {
            QByteArray block = m_dataBlock.left(idx);



            int blockAndBoundaryLength = idx + m_boundary.length();
            m_dataBlock.remove(0,blockAndBoundaryLength);
            //qDebug() << "processBlock(): block length:"<<block.length()<<", blockAndBoundaryLength:"<<blockAndBoundaryLength;

            if(m_firstBlock)
            {
                //QString string = block;
                //qDebug() << "processBlock(): Discarding block since first block flag is true. Dump of block:\n"<<string;
                m_firstBlock = false;
            }
            else
            {
                static const char * eol1 = "\n\n";
                static const char * eol2 = "\r\n\r\n";
                int headerLength = 0;
                if(block.contains(eol2))
                    headerLength = block.indexOf(eol2,0) + 4;
                else
                if(block.contains(eol1))
                    headerLength = block.indexOf(eol1,0) + 2;

                if(headerLength)
                {
                  //  QString header = block.left(headerLength);

                    block.remove(0,headerLength);

                    // Block should now be just data
                  //  qDebug() << "processBlock(): block length:"<<block.length()<<", headerLength:"<<headerLength<<", header:"<<header;

                    if(block.length() > 0)
                    {

                       QImage frame = QImage::fromData(block);

                        if(m_flipImage)//отзеркаливает!
                            frame = frame.mirrored(false,true);


                        if(!frame.isNull())
                        {
                            //qDebug() << "processBlock(): New image received, original size:"<<frame.size()<<", bytes:"<<block.length();

                            if(m_autoResize.width()>0 && m_autoResize.height()>0 &&
                               m_autoResize != frame.size())
                               frame = frame.scaled(m_autoResize);

                            //qDebug() << "processBlock(): Emitting new image, size:"<<frame.size();
                           // emit newImage(frame);
                            myShow(&frame);
                            if (!FlagStorag) FlagStorag=true;//сторож зависания
                        }


                    }
                }

            }

// 			// check for another boundary string in the data before exiting from processBlock()
            idx = m_dataBlock.indexOf(m_boundary);

        }

    }

// 	qDebug() << "processBlock(): End of processing, m_dataBlock.size() remaining:"<<m_dataBlock.size();
}

void MyVideoThread::exit()
{
    if(m_socket)
    {
        m_socket->abort();
        m_socket->disconnectFromHost();
        ///m_socket->waitForDisconnected();
        m_socket->deleteLater();
        ///delete m_socket;
        m_socket = 0;
    }
}


void MyVideoThread::setPollingMode(bool flag)
{
    m_pollMode = flag;
    if(flag)
    {
        exit();
        QTimer::singleShot(1000 / m_pollFps, this, SLOT(pollServer()));
    }
    else
    {
        exit();
        QTimer::singleShot(1000 / m_pollFps, this, SLOT(reconnect()));
    }
}

void MyVideoThread::pollServer()
{
    loadUrl(QString("http://%1:%2%3").arg(m_host).arg(m_port).arg(m_url));
}

void MyVideoThread::SlotStorag()
{
   //qDebug()<<"отработал MyVideoThread::SlotStorag()";
    if (!FlagStorag)
    {
        emit SignalLogView("Завис поток камеры № " +QString::number(NomerPotoka) );
      //  if (!StorogVideoPotok.OnPotok)StorogVideoPotok.OnPotok =true;

       emit reconnect();
    }
    else FlagStorag = false;
    if (!StorogVideoPotok.OnPotok)StorogVideoPotok.OnPotok =true;//сторожевой таймер



}


void MyVideoThread::loadUrl(const QString &location)
{
    QUrl url(location);

    //qDebug() << "MyVideoThread::loadUrl(): url:"<<url;

    QNetworkAccessManager *manager = new QNetworkAccessManager(this);
    connect(manager, SIGNAL(finished(QNetworkReply*)),
        this, SLOT(handleNetworkData(QNetworkReply*)));
    manager->get(QNetworkRequest(url));
}

void MyVideoThread::handleNetworkData(QNetworkReply *networkReply)
{
    //QUrl url = networkReply->url();
    if (!networkReply->error())
    {
        //parseData(QString::fromUtf8(networkReply->readAll()));
        QImage frame = QImage::fromData(networkReply->readAll());
        if(m_flipImage)
            frame = frame.mirrored(true,true);

        if(!frame.isNull())
        {
            //qDebug() << "MyVideoThread::handleNetworkData(): New image received, original size:"<<frame.size()<<", bytes:"<<block.length();

            if(m_autoResize.width()>0 && m_autoResize.height()>0 &&
               m_autoResize != frame.size())
                frame = frame.scaled(m_autoResize);


            //qDebug() << "processBlock(): Emitting new image, size:"<<frame.size();
            emit newImage(frame);
        }

        if(m_pollMode)
        {
            int ms = 1000 / m_pollFps;
            qDebug() << "MyVideoThread::handleNetworkData(): Time till next request:"<<ms<<"ms";
            QTimer::singleShot(ms, this, SLOT(pollServer()));
        }


    }

    networkReply->deleteLater();
    networkReply->manager()->deleteLater();
}

