# -------------------------------------------------
# Project created by QtCreator 2010-01-15T13:44:50
# -------------------------------------------------
TARGET = ucc
TEMPLATE = app
SOURCES += main.cpp \
    mainwindow.cpp \
    PortListener.cpp
HEADERS += mainwindow.h \
    PortListener.h \
    sac.h
FORMS += mainwindow.ui
INCLUDEPATH += ../qextserialport
QMAKE_LIBDIR += ../qextserialport/build
LIBS += -lqextserialport
unix:DEFINES = _TTY_POSIX_
