#-------------------------------------------------
#
# Project created by QtCreator 2013-02-19T15:40:28
#
#-------------------------------------------------

WIN32_CV_INCLUDE = $(OPENCV_INCLUDE)
WIN32_CV_LIB = $(OPENCV_LIB)
OPENCV_VERSION = 243

win32:LIBS += -L$$WIN32_CV_LIB \
                -lopencv_core243 \
                -lopencv_imgproc243 \
                -lopencv_features2d243 \
                -lopencv_gpu243 \
                -lopencv_highgui243 \
                -lopencv_calib3d243 \
                -lopencv_video243
win32:INCLUDEPATH += $$WIN32_CV_INCLUDE

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = VideoObjectDetection
TEMPLATE = app


SOURCES += main.cpp\
        MainWindow.cpp \
    BackgroundFinder.cpp \
    RollingMedianCalculator.cpp \
    RollingAverageCalculator.cpp

HEADERS  += MainWindow.h \
    BackgroundFinder.h \
    RollingMedianCalculator.h \
    RollingAverageCalculator.h

FORMS    += MainWindow.ui
