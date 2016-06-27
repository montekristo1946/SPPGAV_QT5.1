#ifndef MYVIDEOTHREAD_H
#define MYVIDEOTHREAD_H

#include <QObject>
#include <QThread>
#include <QImage>
#include <QDebug>
#include <QString>
#include <iostream>
#include <math.h>
#include <ctype.h>
#include <stdio.h>
#include <QTime>
//#include <QTimer>
#include <QPointer>
#include <QByteArray>
#include <QTcpSocket>
#include <QtNetwork>

#include "readfile.h"
//#include "mjpegclient.h"

#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <opencv/cv.h>

using namespace cv;
using namespace std;
const int M_E_S = 1000;

class MyVideoThread : public QThread
{
    Q_OBJECT
public:
    explicit MyVideoThread(QObject *parent = 0, int NomerPotokat = 0);
    virtual void run();

    volatile struct StorogVideoPotok
    {
        bool OnPotok ;
        bool Storog ;
        bool FirstFrame ;
        int inPeople;
        int outPeople;
        bool SendImege;
        bool WriteVideo;

    }StorogVideoPotok;


///////////////-----видео захват

    bool connectTo(const QString& host, int port=-1, QString url = "/", const QString& user="", const QString& pass="");
    void exit();
    QString errorString(){ return m_socket->errorString(); }

    QSize autoResize() { return m_autoResize; }
    void setAutoResize(QSize size) { m_autoResize = size; }

    bool autoReconnect() { return m_autoReconnect; }
    void setAutoReconnect(bool flag) { m_autoReconnect = flag; }

    QString host() { return m_host; }
    int port() { return m_port; }
    QString path() { return m_url; }

    bool flipImage() { return m_flipImage; }
    void setFlipImage(bool flip) { m_flipImage = flip; }

    bool pollingMode() { return m_pollMode; }
    void setPollingMode(bool flag);

    int pollingFps() { return m_pollFps; }
    void setPollingFps(int fps) { m_pollFps = fps; }
///////////////---------

private:
    ~MyVideoThread();
    QSettings* settingsReestr;

    Mat qimage2mat(const QImage& qimage);
    CvSize size;
    Mat image;
    Mat frame;
     Mat frame1;
    Mat fore;
    //VideoCapture * capture;
    VideoWriter * record;
    int frameRate;
    QImage qimage;
    //QTimer timeStorag;

    QString PutCamera;

    void FunkVichislenie();
    Readfile * MyReadfile;
    void initPainter();



    //////////////////////////////////////////СПП

    void TrainBackground(Mat* image);
    void MotionDetection(Mat *image, float porog);
    int contrastFilter(Mat* in);
    int FStrukturaKrugntKoll();
    int FStrukturaKrugntKollPeople();
    void FStrukturaObnulenie();
    void FunkObedinenie();
    void FunkPodscheta();
    void FunkPodschetPeopleObnuleniy();
    void MywaitKey(int tmp = 0);//задержка
    QTime TimeNow; //для анализа времини выполнения!


    Mat cacheFrame; // фоновый кадр!
   // int InPepleTmp;
   // int OutPepleTmp;
    float porog;

    //float *m;

    int BackgroundUpdatetmp;
    Mat kern;
    std::vector<std::vector<cv::Point> >contours;

    int InPeple;
    int OutPeple;
    int MaxKrug ;// рамер мах круга
    int MinKrug ;// рамер минимального круга
    int line1 ;//линия пересечени
    int line4 ;//линия пересечени
    int line5 ;//линия пересечени
    int Livepeople ;//время жизни круга
    int PorogPerekritiy ; // допустимая величина наложение кругов
    int KrugCheloveka ;//постоянная велечена круга человека
    int RastoynieMegduChelami ;// фиксированое расстояние между обьектами которые движутся!
    float porogSetup ; //порог чуствительности
    int BackgroundUpdate ;//частота обновления фона 5минут /24 кадра - 7200
    int InstantaneousContrast; //мгновенная контрастность (8)
    int NomerPotoka;

    int line2 ;//линия пересечени
    int line3 ;//линия пересечени


    std::ostringstream inPOstring;//переменны для перевода из INT в std::string
    std::ostringstream outPOstring;

    struct StrukturaKrug
    {
        CvPoint center;
        double radius;
        bool risovat ;
        bool zapolnen ;

    } StrukturaKrug[M_E_S];


    struct StrukturaPodschetPeople
    {
        CvPoint center;
        double radius;
        int TimeLive;//лимит жизни pipla
        bool zapolnen ;
        bool line1 ;
        bool line2 ;
        bool risovat ;
    }StrukturaPodschetPeople[M_E_S];



////////////////-видеозахват
    void log(const QString&);
    QTcpSocket *m_socket;

    QString m_boundary;
    bool m_firstBlock;

    QByteArray m_dataBlock;


    QSize m_autoResize;
    bool m_autoReconnect;

    QString m_host;
    int m_port;
    QString m_url;
    QString m_user;
    QString m_pass;

    bool m_flipImage;
    bool m_pollMode;
    int  m_pollFps;
    bool FlagStorag;

    QTimer TimerStorag;
    QString ConnectIP;
    int ConnectPort;
    QString ConnectUrl;
    QString ConnectLogin;
    QString ConnectPass;
    int WidthFrame;
    int HeightFrame;



////////////////


signals:
    void MySendDataVideFrame( QPixmap image);
    void SendEndThread( QString);
    void SignalLogView(QString tmp);
    void SignalDisconnect();

////////////////-видеозахват
    void socketDisconnected();
    void socketError(QAbstractSocket::SocketError);
    void socketConnected();

    void newImage(QImage);
    void SignalFirstFrame();
////////////////


public slots:
    void SlotExitThread();
    void myShow(QImage *qimagetmp);
    void SlotlFirstFrame();


private slots:
 void StoragAlarm();

////////////////-видеозахват
 void dataReady();
 void processBlock();
 void lostConnection();
 void lostConnection(QAbstractSocket::SocketError);
 void reconnect();
 void connectionReady();
 void loadUrl(const QString &url);
 void handleNetworkData(QNetworkReply *networkReply);
 void pollServer();

 void SlotStorag();

 ////////////////



};

#endif // MYVIDEOTHREAD_H
