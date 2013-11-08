# -------------------------------------------------
# Project created by QtCreator 2010-01-15T13:44:50
# -------------------------------------------------
TARGET = ucc
TEMPLATE = app
SOURCES += main.cpp \
    mainwindow.cpp \
    PortListener.cpp \
    vacio.cpp
HEADERS += mainwindow.h \
    PortListener.h \
    sac.h \
    vacio.h
FORMS += mainwindow.ui
LIBS += -lqextserialport
unix:DEFINES = _TTY_POSIX_
RESOURCES += resources.qrc
