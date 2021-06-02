TEMPLATE = lib
TARGET = log_helper

CONFIG += plugin c++11
CONFIG -= qt


unix {
    LIBS += -lpthread
    LIBS += -L"$$PWD/../lib/linux/log4cxx" -llog4cxx -lapr-1 -laprutil-1 -lcrypto -lexpat -lssl
    DESTDIR += $$PWD/../bin/linux
}


INCLUDEPATH += \
    $$PWD/../src \
    $$PWD/../inc


HEADERS += \
    $$PWD/src/log4cxxhelper.h


SOURCES += \
    $$PWD/src/log4cxxhelper.cpp







