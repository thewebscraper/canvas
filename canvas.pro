#-------------------------------------------------
#
# Project created by QtCreator 2016-05-25T10:25:38
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = canvas
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
        imgproc.cpp

HEADERS  += mainwindow.h \
        imgproc.h

FORMS    += mainwindow.ui

LIBS += -LC:\\OpenCV2.4.10\\opencv\\build\\x64\\vc11\\lib \
    -lopencv_core2410 \
    -lopencv_highgui2410 \
    -lopencv_imgproc2410 \
    -lopencv_features2d2410 \
    -lopencv_calib3d2410

INCLUDEPATH += C:\\OpenCV2.4.10\\opencv\\build\\include
