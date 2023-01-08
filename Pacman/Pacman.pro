TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        main.cpp \
        module/convertImgMat.cpp \
        module/gameSprite.cpp \
        module/movement.cpp
        module/convertImgMat.cpp

include(MinGL2/mingl.pri)

HEADERS += \
    module/gameSprite.h \
    module/convertImgMat.h \
    module/movement.h \
    module/type.h
