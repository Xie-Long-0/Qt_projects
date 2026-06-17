#-------------------------------------------------
#
# Project created by QtCreator 2017-10-04T14:43:02
#
#-------------------------------------------------

QT       += core gui widgets

greaterThan(QT_MAJOR_VERSION, 6): CONFIG += c++17

TARGET = CustomListWidget
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

msvc {
    QMAKE_CXXFLAGS += /utf-8
}

SOURCES += \
        CustomListItemWidget.cpp \
        main.cpp \
        widget.cpp

HEADERS += \
        CustomListItemWidget.h \
        widget.h

FORMS += \
        CustomListItemWidget.ui \
        widget.ui
