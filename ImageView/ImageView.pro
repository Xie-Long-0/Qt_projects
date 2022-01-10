QT       += core gui widgets

greaterThan(QT_MAJOR_VERSION, 6): CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

release {
    DESTDIR = ./release
}

debug {
    DESTDIR = ./debug
    CONFIG += console
}

OBJECTS_DIR = $$DESTDIR/obj
MOC_DIR = $$DESTDIR/moc
RCC_DIR = $$DESTDIR/qrc
UI_DIR = $$DESTDIR/ui

SOURCES += \
    main.cpp \
    widget.cpp \
    graphicview.cpp

HEADERS += \
    widget.h \
    graphicview.h

FORMS += \
    widget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
