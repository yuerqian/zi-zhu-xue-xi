HEADERS += \
    mywidget.h \
    ../mybutton/mybutton.h

SOURCES += \
    mywidget.cpp \
    ../mybutton/mybutton.cpp

QT +=widgets gui

INCLUDEPATH +=../mybutton/

CONFIG +=C++11;
