QT += core gui widgets

TEMPLATE = app
TARGET = STL_read

CONFIG += c++17 debug_and_release debug_and_release_target build_all

HEADERS += ./STL_read.h

SOURCES += ./STL_read.cpp \
    ./main.cpp

FORMS += ./STL_read.ui

win32:RC_FILE = STL_read.rc
