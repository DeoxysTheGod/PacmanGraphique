TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        main.cpp \
        module/gameSprite.cpp

include(MinGL2/mingl.pri)

HEADERS += \
    module/gameSprite.h \
    module/type.h
