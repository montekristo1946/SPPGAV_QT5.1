#include <QApplication>


#include <QtGui>
#include "mainwindow.h"

int main(int argc, char *argv[])
{

  QApplication a(argc, argv);
 QApplication::setQuitOnLastWindowClosed(false);

    MainWindow w;

 w.hide();
 // w.show();
    return a.exec();
}
