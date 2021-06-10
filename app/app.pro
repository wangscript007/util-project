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
    LIBS += -L"$$PWD/../lib/linux/mongoclient" -lbson-1.0 -lmongoc-1.0 -lbsoncxx -lmongocxx
    LIBS += -L"$$PWD/../bin/linux" -llog_helper -lmongo_client_driver
    DESTDIR = $$PWD/../bin/linux
}


INCLUDEPATH += \
    $$PWD/src \
    $$PWD/../inc \
    $$PWD/../inc/mongoclient \
    $$PWD/../inc/mongoclient/libbson-1.0 \
    $$PWD/../inc/mongoclient/libmongoc-1.0 \
    $$PWD/../inc/mongoclient/bsoncxx/v_noabi \
    $$PWD/../inc/mongoclient/mongocxx/v_noabi \
    $$PWD/../log/src \
    $$PWD/../mongoclientdriver/src


HEADERS += \
    $$PWD/src/exceptionutil.h


SOURCES += \
    $$PWD/src/exceptionutil.cpp \
    $$PWD/src/main.cpp










