QT       += core gui network gui-private

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

TEMPLATE = app

win32:{
    NAME_PO = uQtLoad

    VERSION = 0.0.1
    QMAKE_TARGET_COMPANY = CEREGATOR
    QMAKE_TARGET_COPYRIGHT = CEREGATOR
    QMAKE_TARGET_PRODUCT = $${NAME_PO}
    QMAKE_TARGET_DESCRIPTION = unofficial Qt loader 

    RC_ICONS = $$PWD/image/logo.ico
}

win32{
    UI_DIR = tmp/form_h
    MOC_DIR = tmp/moc
    OBJECTS_DIR = tmp/obj
    RCC_DIR = tmp/rcc
    DESTDIR = output
}

contains(QT_ARCH, x86_64){
    TARGET = $${NAME_PO}_v$${VERSION}_x64
}

contains(QT_ARCH, i386){
    TARGET = $${NAME_PO}_v$${VERSION}_x32
}

SOURCES += \
    componentpage.cpp \
    downloader.cpp \
    main.cpp \
    mainwindow.cpp \
    mirrorsettings.cpp \
    savepage.cpp

HEADERS += \
    componentpage.h \
    downloader.h \
    mainwindow.h \
    mirrorsettings.h \
    savepage.h

FORMS += \
    componentpage.ui \
    mainwindow.ui \
    mirrorsettings.ui \
    savepage.ui

include(q7zip/7z/7zip.pri)
INCLUDEPATH += q7zip/include
#LIBS += -Lq7zip/7z -l7z
#LIBS += -Lq7zip/7z -l7zd
LIBS += -Lq7zip/lib -lq7z

