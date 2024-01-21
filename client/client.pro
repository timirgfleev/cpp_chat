TEMPLATE = app
TARGET = client
INCLUDEPATH += .

# Input
# HEADERS += include.h
SOURCES += main.cpp

QT += core gui network
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets