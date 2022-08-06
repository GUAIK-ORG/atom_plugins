QT += widgets

TEMPLATE = lib
DEFINES += ATOMPLUGIN_LIBRARY
CONFIG += c++11

TARGET = {{id}}

QMAKE_CXXFLAGS_RELEASE = $$QMAKE_CFLAGS_RELEASE_WITH_DEBUGINFO
QMAKE_LFLAGS_RELEASE = $$QMAKE_LFLAGS_RELEASE_WITH_DEBUGINFO

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
    atomplugin.cpp \
    {{widget_cpps}}

HEADERS += \
    atomplugin_global.h \
    atomplugin.h \
    icontext.h \
    iplugin.h \
    iwindow.h \
    ifont.h \
    ilog.h \
    imq.h \
    imessage.h \
    istorage.h \
    ievent.h \
    {{widget_hs}}

DISTFILES += \
    {{id}}.yml

FORMS += \
    {{widget_uis}}
