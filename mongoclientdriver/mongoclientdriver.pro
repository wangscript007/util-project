TEMPLATE = lib
TARGET = mongo_client_driver

CONFIG += plugin c++11
CONFIG -= qt


unix {
    LIBS += -L"$$PWD/../lib/linux/mongoclient" -lmongocxx-static -lmongoc-1.0 -lbsoncxx-static -lbson-static-1.0 \
                                               -lssl -lcrypto -lz
    DESTDIR += $$PWD/../bin/linux
}


INCLUDEPATH += \
    $$PWD/src \
    $$PWD/../inc \
    $$PWD/../inc/mongoclient \
    $$PWD/../inc/mongoclient/bson \
    $$PWD/../inc/mongoclient/mongoc \
    $$PWD/../inc/mongoclient/bsoncxx \
    $$PWD/../inc/mongoclient/mongocxx


HEADERS += \
    $$PWD/src/mongoclientdriverutil.h


SOURCES += \
    $$PWD/src/mongoclientdriverutil.cpp


