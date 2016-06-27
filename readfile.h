#ifndef READFILE_H
#define READFILE_H

#include <QObject>
#include <QSettings>
#include <QFile>
#include <QDir>
//#include <QDebug>
#include <QTextStream>
#include <QDate>
#include <QDir>

//для шифровалки
//#include <openssl/evp.h>
//#include <openssl/aes.h>
//#include <mbstring.h>


#include <QTextCodec>
#include <QMessageBox>
#include "mycrypto.h"


#define BUFSIZE 1024

class Readfile : public QObject
{
    Q_OBJECT
public:
     ~Readfile();
    explicit Readfile(QObject *parent = 0);
    bool VriteSetting(QString parametr, QString znachenie, QString NomerVideo);
    QString ReadSetting(QString parametr, QString NomerVideo = "1");
    void PerviyStartParametr();
    bool WriteReports(QString Nomerprohoda,QString InPeople,QString OutPeople);
    bool WriteDebugLOG(QString);

   // QString myCryptTmp(QString inText,int mode);

signals:
    void SignalLogView(QString tmp);

private:

    QString inPass;
    QString myCrypt(QString inText,int mode=0);

    QSettings* settings;
    QSettings* settingsReestr;
    MyCrypto * Crypt;

    QString IDD;
    QString inTimePodshet;
    QString ImyFile;



public slots:

};

#endif // READFILE_H
