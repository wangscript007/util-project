TEMPLATE = app
TARGET = app

CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt


unix {
    LIBS += -lpthread
    LIBS += -L"$$PWD/../lib/linux" -llog4cxx -lapr-1 -laprutil-1 -lcrypto -lexpat -lssl
    LIBS += -L"$$PWD/../bin/linux" -llog_helper
    DESTDIR = $$PWD/../bin/linux
}


INCLUDEPATH += \
    $$PWD/../src \
    $$PWD/../inc \
    $$PWD/../log/src


SOURCES += \
    $$PWD/src/main.cpp







