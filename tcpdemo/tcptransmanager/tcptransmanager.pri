
QT += network

INCLUDEPATH += $$PWD

HEADERS += \
    $$PWD/llstcpdef.h \
    $$PWD/llstcptransbase.h \
    $$PWD/llstcptransclient.h \
    $$PWD/llstcptransserver.h

SOURCES += \
    $$PWD/llstcptransbase.cpp \
    $$PWD/llstcptransclient.cpp \
    $$PWD/llstcptransserver.cpp
