#-------------------------------------------------
#
# Project created by QtCreator 2015-02-12T16:45:57
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = detectCV
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    ObjectExtractor.cpp

CONFIG += c++11
QMAKE_MACOSX_DEPLOYMENT_TARGET = 10.9

INCLUDEPATH += /usr/local/include

LIBS += -L/usr/local/lib

LIBS += -lopencv_calib3d \
-lopencv_contrib \
-lopencv_core \
-lopencv_features2d \
-lopencv_flann \
-lopencv_gpu \
-lopencv_highgui \
-lopencv_imgproc \
-lopencv_legacy \
-lopencv_ml \
-lopencv_objdetect \
-lopencv_video

HEADERS += \
    ObjectExtractor.h

OTHER_FILES += \
    testframe_3.jpg
