#ifndef FTP_H
#define FTP_H

#include <QObject>
#include<QNetworkAccessManager>
#include<QNetworkReply>
 #include <QEventLoop>
#include<QFile>
//#include <QDebug>
#include <QDir>
#include <QDate>
#include <QString>
#include <QThread>
#include <QTimer>
#include "readfile.h"

class Ftp : public QThread

{
    Q_OBJECT
public:
    explicit Ftp(QObject *parent = 0);
    virtual void run();
    volatile bool AllLogs;

    ~Ftp();


    bool OtpravkaFTP_2(QString setting ="");
    bool ObrabotkaHranilicha_2(QStringList *inHranlish, QString inPutFile = "");
    QString PoiskPosledyuFail_2(QStringList *inHranlish);

private:

    bool GetFile(QString LoginFtp, QString PasswordFtp,int port,QString UrlFtp,QString FileOutFtp);

    QSettings* settingsReestr;
    QNetworkAccessManager* manager;
    QNetworkReply * reply;
    QString ImyFile;
    QString LoginFtp;
    QString PasswordFtp;
    int port;
    QString UrlSetting;
    QString IDD;
    QTimer *timerDeletClass;

signals:
    void SignalLogView(QString tmp);
    void SignalStorag();
    void SignalStopAlarm();

public slots:
    void doCleaning();
    void SlotExitThread();
    void SlotStorag();
    void SlotVievDownload(qint64,qint64);
    void SlotErrorDownload(QNetworkReply::NetworkError);

};

#endif // FTP_H


