TEMPLATE = lib
TARGET = mongo_client_driver

CONFIG += plugin c++11
CONFIG -= qt


unix {
    LIBS += -L"$$PWD/../lib/linux/mongoclient" -lbson-1.0 -lmongoc-1.0 -lbsoncxx -lmongocxx
    DESTDIR += $$PWD/../bin/linux
}


INCLUDEPATH += \
    $$PWD/src \
    $$PWD/../inc \
    $$PWD/../inc/mongoclient \
    $$PWD/../inc/mongoclient/libbson-1.0 \
    $$PWD/../inc/mongoclient/libmongoc-1.0 \
    $$PWD/../inc/mongoclient/bsoncxx/v_noabi \
    $$PWD/../inc/mongoclient/mongocxx/v_noabi


HEADERS += \
    $$PWD/src/mongoclientdriverutil.h


SOURCES += \
    $$PWD/src/mongoclientdriverutil.cpp


