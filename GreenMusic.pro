#-------------------------------------------------
#
# Project created by QtCreator 2013-11-02T16:16:34
#
#-------------------------------------------------

QT       += core gui phonon svg

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = GreenMusic
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    cmusicview.cpp \
    ../GraphicsWidgetLib/cgraphicswidget.cpp \
    ../GraphicsWidgetLib/csvgwidget.cpp \
    ../GraphicsWidgetLib/cimgwidget.cpp \
    ../GraphicsWidgetLib/ctextwidget.cpp \
    ../GraphicsWidgetLib/ctexteditor.cpp \
    ../GraphicsWidgetLib/cwidgetlist.cpp \
    cplaylist.cpp \
    ../GraphicsWidgetLib/cmessagewidget.cpp \
    ../GraphicsWidgetLib/cbuttonwidget.cpp \
    cmenuspot.cpp

HEADERS  += mainwindow.h \
    cmusicview.h \
    gconfig.h \
    ../GraphicsWidgetLib/cgraphicswidget.h \
    ../GraphicsWidgetLib/csvgwidget.h \
    ../GraphicsWidgetLib/cimgwidget.h \
    ../GraphicsWidgetLib/ctextwidget.h \
    ../GraphicsWidgetLib/ctexteditor.h \
    ../GraphicsWidgetLib/cwidgetlist.h \
    cplaylist.h \
    ../GraphicsWidgetLib/cmessagewidget.h \
    ../GraphicsWidgetLib/cbuttonwidget.h \
    cmenuspot.h

RESOURCES += \
    res.qrc
