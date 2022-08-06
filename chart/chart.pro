QT += widgets

TEMPLATE = lib
DEFINES += ATOMPLUGIN_LIBRARY
CONFIG += c++11

TARGET = chart

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


INCLUDEPATH += \
    ../framework

SOURCES += \
    chartbase.cpp \
    coordsys.cpp \
    atomplugin.cpp \
    spectrum.cpp

HEADERS += \
    atomplugin_global.h \
    chartbase.h \
    coordsys.h \
    atomplugin.h \
    icontext.h \
    iplugin.h \
    iwindow.h \
    ilog.h \
    imq.h \
    imessage.h \
    istorage.h \
    spectrum.h \

DISTFILES += \
    chart.yml
