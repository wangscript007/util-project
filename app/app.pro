TEMPLATE = app
TARGET = app

CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt


unix {
    LIBS += -L"$$PWD/../bin/linux" -llog_helper -lmongo_client_driver
    LIBS += -L"$$PWD/../lib/linux/log4cxx" -llog4cxx -lapr-1 -laprutil-1 -lcrypto -lexpat -lssl
    LIBS += -L"$$PWD/../lib/linux/evpp" -levpp_static -levpp_boost_static -levnsq_static -levmc_static \
                                        -levpp_lite_static -lglog -lgflags -levent -levent_core -levent_extra
    LIBS += -L"$$PWD/../lib/linux/mongoclient" -lmongocxx-static -lmongoc-1.0 -lbsoncxx-static -lbson-static-1.0 \
                                               -lssl -lcrypto -lz
    LIBS += -lpthread -pthread -ldl -lrt -lm -lresolv
    #LIBS += -L"/usr/lib/x86_64-linux-gnu" -ldl -lrt -lm
    #QMAKE_LIBDIR += -ldl -lrt

    DESTDIR = $$PWD/../bin/linux
}


INCLUDEPATH += \
    $$PWD/src \
    $$PWD/../inc \
    $$PWD/../inc/mongoclient \
    $$PWD/../inc/mongoclient/bson \
    $$PWD/../inc/mongoclient/mongoc \
    $$PWD/../inc/mongoclient/bsoncxx \
    $$PWD/../inc/mongoclient/mongocxx \
    $$PWD/../log/src \
    $$PWD/../mongoclientdriver/src


HEADERS += \
    $$PWD/src/exceptionutil.h


SOURCES += \
    $$PWD/src/exceptionutil.cpp \
    $$PWD/src/main.cpp


