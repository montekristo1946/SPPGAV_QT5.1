#ifndef RUNPOTOK_H
#define RUNPOTOK_H

#include <QApplication>
#include <QObject>
#include <QDir>
#include <QDebug>
#include <QMessageBox>
#include <QThread>
#include <QString>
#include <QString>


class RunPotok : public QThread
{
    Q_OBJECT
public:

   /* RunPotok(QObject * parent = 0 ) : QThread(parent)
    {
        moveToThread(this);
    }

    virtual void run()
    {
        //делаем что то в контексте нового потока

        exec();			//запускаем обработку очереди сообщений потока
    }*/

protected slots:
    void 	receiveSignal();
};

#endif // RUNPOTOK_H


