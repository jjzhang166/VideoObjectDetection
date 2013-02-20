#-------------------------------------------------
#
# Project created by QtCreator 2013-02-19T15:40:28
#
#-------------------------------------------------

WIN32_CV_INCLUDE = $(OPENCV_INCLUDE)
WIN32_CV_LIB = $(OPENCV_LIB)
OPENCV_VERSION = 243

win32:LIBS += -L$$WIN32_CV_LIB \
                -lopencv_core \
                -lopencv_imgproc \
                -lopencv_features2d \
                -lopencv_gpu \
                -lopencv_highgui \
                -lopencv_calib3d \
                -lopencv_video
win32:INCLUDEPATH += $$WIN32_CV_INCLUDE

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = VideoObjectDetection
TEMPLATE = app


SOURCES += main.cpp\
        MainWindow.cpp

HEADERS  += MainWindow.h

FORMS    += MainWindow.ui
