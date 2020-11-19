TEMPLATE = app
TARGET = scutbci_gui

QT = core gui network concurrent xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    flashbutton.cpp \
    hrtimer.cpp \
    tcpserver.cpp


HEADERS += \
    mainwindow.h \
    flashbutton.h \
    hrtimer.h \
    sockethandler.h \
    protocol.h \
    tcpserver.h


FORMS += \
    mainwindow.ui \
