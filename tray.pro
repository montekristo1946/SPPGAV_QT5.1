#-------------------------------------------------
#
# Project created by QtCreator 2011-02-28T19:08:15
#
#-------------------------------------------------

QT       += core gui network
QT       += widgets
TARGET = tray
TEMPLATE = app
CONFIG += thread



INCLUDEPATH += "d:/opencv/opencv_qt/include"

#INCLUDEPATH += –I d:\opencv\openssl-0.9.8l\inc32\
#LIBS += d:\opencv\openssl-0.9.8l\out32\ssleay32.a
#LIBS += d:\opencv\openssl-0.9.8l\out32\libeay32.a


LIBS+=d:/opencv/opencv_qt/lib/libopencv_calib3d249.dll.a
LIBS+=d:/opencv/opencv_qt/lib/libopencv_contrib249.dll.a
LIBS+=d:/opencv/opencv_qt/lib/libopencv_core249.dll.a
LIBS+=d:/opencv/opencv_qt/lib/libopencv_features2d249.dll.a
LIBS+=d:/opencv/opencv_qt/lib/libopencv_flann249.dll.a
LIBS+=d:/opencv/opencv_qt/lib/libopencv_gpu249.dll.a
LIBS+=d:/opencv/opencv_qt/lib/libopencv_highgui249.dll.a
LIBS+=d:/opencv/opencv_qt/lib/libopencv_imgproc249.dll.a
LIBS+=d:/opencv/opencv_qt/lib/libopencv_legacy249.dll.a
LIBS+=d:/opencv/opencv_qt/lib/libopencv_ml249.dll.a
LIBS+=d:/opencv/opencv_qt/lib/libopencv_nonfree249.dll.a
LIBS+=d:/opencv/opencv_qt/lib/libopencv_objdetect249.dll.a
LIBS+=d:/opencv/opencv_qt/lib/libopencv_ocl249.dll.a
LIBS+=d:/opencv/opencv_qt/lib/libopencv_photo249.dll.a
LIBS+=d:/opencv/opencv_qt/lib/libopencv_stitching249.dll.a
LIBS+=d:/opencv/opencv_qt/lib/libopencv_superres249.dll.a
LIBS+=d:/opencv/opencv_qt/lib/libopencv_ts249.a
LIBS+=d:/opencv/opencv_qt/lib/libopencv_video249.dll.a
LIBS+=d:/opencv/opencv_qt/lib/libopencv_videostab249.dll.a


SOURCES += main.cpp\
        mainwindow.cpp \
    myvideothread.cpp \
    nastrkamerdialog.cpp \
    readfile.cpp \
    nastrparamkamdialog.cpp \
    ftpdialog.cpp \
    ftp.cpp \
    ping.cpp \
    myinfo.cpp \
    mycrypto.cpp

HEADERS  += mainwindow.h \
   myvideothread.h \
    nastrkamerdialog.h \
    readfile.h \
    nastrparamkamdialog.h \
    ftpdialog.h \
    ftp.h \
    ping.h \
    myinfo.h \
    mycrypto.h

FORMS    += mainwindow.ui \
    nastrkamerdialog.ui \
    nastrparamkamdialog.ui \
    ftpdialog.ui \
    ping.ui \
    myinfo.ui

RESOURCES += \
    res.qrc

RC_FILE = appIcon.rc
