HEADERS += \
    mywidget.h \
    tcpserver.h \
    tcpclient.h \
    chooseinterface.h \
    udpsever.h \
    udpclient.h

SOURCES += \
    mywidget.cpp \
    tcpserver.cpp \
    tcpclient.cpp \
    chooseinterface.cpp \
    udpsever.cpp \
    udpclient.cpp

QT +=widgets network gui

CONFIG += C11
