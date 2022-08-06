QT += widgets network sql

TEMPLATE = lib
DEFINES += ATOMPLUGIN_LIBRARY
CONFIG += c++11

TARGET = net

QMAKE_CXXFLAGS_RELEASE = $$QMAKE_CFLAGS_RELEASE_WITH_DEBUGINFO
QMAKE_LFLAGS_RELEASE = $$QMAKE_LFLAGS_RELEASE_WITH_DEBUGINFO

macx {
    ROOTPATH = $$PWD/../../bin
    APPPATH = $$ROOTPATH/gkf.app/Contents/MacOS
    PLUGINPATH = $$APPPATH/plugin
    DESTDIR = $$PLUGINPATH/$$TARGET
    QMAKE_POST_LINK += cp $$PWD/$${TARGET}.yml $$DESTDIR/$${TARGET}.yml $$escape_expand(\\n\\t)
}

win32 {
    ROOTPATH = $$PWD/../../bin
    ROOTPATH ~= s,/,\\,g

    PLUGINPATH = $$ROOTPATH/plugin
    PLUGINPATH ~= s,/,\\,g

    SRC_DIR = $$PWD
    SRC_DIR ~= s,/,\\,g

    DESTDIR = $${PLUGINPATH}\\$${TARGET}

    QMAKE_POST_LINK += $$QMAKE_COPY_DIR  $$shell_quote($${SRC_DIR}\\$${TARGET}.yml) $$shell_quote($${DESTDIR}\\) $$escape_expand(\\n\\t)
}

win32 {
     LIBS += -lWs2_32
}


INCLUDEPATH += \
    ../framework

SOURCES += \
    atomplugin.cpp \
    netservice.cpp \
    tcp/keepalive.cpp \
    tcp/session.cpp \
    tcp/tcpclient.cpp \
    tcp/tcpserver.cpp \
    tcp/tcpsocket.cpp

HEADERS += \
    atomplugin_global.h \
    atomplugin.h \
    icontext.h \
    iplugin.h \
    iwindow.h \
    ilog.h \
    imq.h \
    imessage.h \
    inetservice.h \
    netbase.h \
    netservice.h \
    tcp/keepalive.h \
    tcp/session.h \
    tcp/tcpclient.h \
    tcp/tcpserver.h \
    tcp/tcpsocket.h

DISTFILES += \
    net.yml
