#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMenu>
#include <QMessageBox>
#include <QTimer>
#include <QMainWindow>
#include <QSystemTrayIcon>
#include <QTime>
#include <QPointer>
#include <QThread>
//#include <QtConcurrent/QtConcurrentRun>
#include <QFuture>

//#include "windows.h"


#include "myvideothread.h"
#include "nastrkamerdialog.h"
#include "readfile.h"
#include "ftp.h"
#include "ftpdialog.h"
#include "nastrparamkamdialog.h"
#include "ping.h"
#include "myinfo.h"




namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
   // MyVideoThread* VideoPotok1;
    QPointer<MyVideoThread> VideoPotok1;
    QPointer<MyVideoThread> VideoPotok2;
    QPointer<MyVideoThread> VideoPotok3;
    QPointer<MyVideoThread> VideoPotok4;
    QPointer<MyVideoThread> VideoPotok5;
    QPointer<MyVideoThread> VideoPotok6;

public slots:
     void SlotLogView(QString);



private slots:
    void changeEvent(QEvent*);
    void trayIconActivated(QSystemTrayIcon::ActivationReason reason);
    void trayActionExecute();
    void setTrayIconActions();
    void showTrayIcon();

    void on_action1_triggered();
  //  void on_pushButton_clicked();
  //  void on_pushButton_2_clicked();


    void SlotConnektThreadVideo_1(QString);
    void FTPAlarm();
    void StoragAlarm();
    void SlotPerenosDanuPotokAlarm();
    void DeleVideoFile();
    void SlotAllStartPotok();
     void PutFtp();
     void LisCensiy();




    void on_action2_triggered();

    void on_action_3_triggered();

    void on_pushButton_3_clicked();

    void on_action_triggered();

    void on_action_2_triggered();

private:
    Ui::MainWindow *ui;
    QMenu *trayIconMenu;
    QAction *minimizeAction;
    QAction *restoreAction;
    QAction *quitAction;
    QSystemTrayIcon *trayIcon;

   QPointer<NastrParamKamDialog> MyNastrParamKamDialog;
    QPointer<NastrKamerDialog> NastroykaKamerDialog;

    int AllFTPAlarm;
    QString TimeLogFtp;

///////////////Отладака удали!
//QSettings *settings_1;

/////////////////

   // QPointer<MyVideoThread> VideoPotok1;
struct StruktAllStartPotok
{
    bool potok_1;
    bool potok_2;
    bool potok_3;
    bool potok_4;
    bool potok_5;
    bool potok_6;

}StruktAllStartPotok;

   // QTimer timerAllStartPotok;
    QTimer timerFTP;
    QTimer timerFTPAll;

    QTimer timerAlarm;
    QTimer timerPerenosDanuPotokAlarm;

    Readfile* MyReadfile;
    Ftp* myFtp;
    QPointer<FTPDialog> ftpDialog;
    QPointer<Ping> myPing;
   /* Ftp * myFtp;
    FTPDialog * ftpDialog;
    Ping * myPing;*/

    bool OnVideiopotok1;
    bool OnVideiopotok2;
    bool OnVideiopotok3;
    bool OnVideiopotok4;
    bool OnVideiopotok5;
    bool OnVideiopotok6;

    bool WriteVideio;

    bool FtpFlag;



    struct StorogVideoPotokMain
    {
        int inPeople;
        int outPeople;
    }StorogVideoPotokMain[6];

    void initPainter();

    bool TimeAnalis(QString tmp = "NULL");
    bool TimeAnalisTimeWriteVideo();

    QTime timeSystem;
QTime timeON;
QTime timeOFF;
QTime TimeLogNow;
QDate DateLogNow;
QTime timeTmp;

QTime timeOnWriteVideo;
QTime timeOffWriteVideo;

QSettings* settingsReestr;

signals:
void SignalExitThread_1();
void SignalExitThread_2();
void SignalExitThread_3();
void SignalExitThread_4();
void SignalExitThread_5();
void SignalExitThread_6();



};


#endif // MAINWINDOW_H
