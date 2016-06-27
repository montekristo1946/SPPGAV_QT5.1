#ifndef MYTHREAD_H
#define MYTHREAD_H

#include <QObject>
#include <QThread>
#include <QDebug>
#include <QString>
#include <QFuture>
#include <QtConcurrent/QtConcurrentRun>

#include <QTimer>

#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <opencv/cv.h>

using namespace cv;

class MyThread : public QThread
{
    Q_OBJECT
public:
    explicit MyThread(QObject *parent = 0);


    void run( );

    void myVideo(QString tmp);



    Mat mat;
    VideoCapture capture;

private slots:
    void processFrameAndUpdateGui();

protected slots:

private:
   QTimer *timer;

signals:

public slots:

};

#endif // MYTHREAD_H
