TEMPLATE = app
TARGET = app

CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt


unix {
    LIBS += -lpthread
    LIBS += -L"$$PWD/../lib/linux/log4cxx" -llog4cxx -lapr-1 -laprutil-1 -lcrypto -lexpat -lssl
    LIBS += -L"$$PWD/../lib/linux/evpp" -levpp_static -levpp_boost_static -levnsq_static -levmc_static \
                                        -levpp_lite_static -lglog -lgflags -levent -levent_core -levent_extra
    LIBS += -L"$$PWD/../bin/linux" -llog_helper
    DESTDIR = $$PWD/../bin/linux
}


INCLUDEPATH += \
    $$PWD/../src \
    $$PWD/../inc \
    $$PWD/../log/src


SOURCES += \
    $$PWD/src/main.cpp







