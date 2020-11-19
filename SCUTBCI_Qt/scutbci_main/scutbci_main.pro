TEMPLATE = app
TARGET = scutbci_main

QT = core gui network concurrent xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

INCLUDEPATH += $$PWD/libs \
    "D:\sdk\eigen\eigen" \
#    "C:\Program Files\MATLAB\R2016b\extern\include" \

# LIBS += -L"C:\Program Files\MATLAB\R2016b\extern\lib\win64\microsoft" \
#     -llibmx -llibeng

# INCLUDEPATH += $$PWD/libs \
#     "D:\sdk\eigen\eigen" \
#     "C:\Program Files\MATLAB\R2008b\extern\include" \
#
# LIBS += -L"C:\Program Files (x86)\MATLAB\R2008b\extern\lib\win32\microsoft" \
#     -llibmx -llibeng

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    tcpclient.cpp \
    amptransport.cpp \
    epochmanager.cpp \
    netreader.cpp \
    netmarker.cpp \
    netactuator.cpp \
    eeggraph.cpp \
    eegalgoeng.cpp \
    eegalgocpp.cpp \
    linearclassifier.cpp \
    tcpclientmt.cpp \
    hrtimer.cpp \
    udpclient.cpp \
    netpresenter.cpp


HEADERS += \
    mainwindow.h \
    tcpclient.h \
    amptransport.h \
    epochmanager.h \
    netreader.h \
    netmarker.h \
    netactuator.h \
    eeggraph.h \
    eegalgoeng.h \
    eegalgocpp.h \
    linearclassifier.h \
    signalprocess.h \
    matrixx.h \
    tcpclientmt.h \
    hrtimer.h \
    iobuffer.h \
    udpclient.h \
    sockethandler.h \
    protocol.h \
    netpresenter.h


FORMS += \
    mainwindow.ui \
    netreader.ui \
    netmarker.ui \
    netactuator.ui \
    netpresenter.ui

RESOURCES += \
    resources.qrc
