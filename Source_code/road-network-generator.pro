TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

CONFIG += link_pkgconfig
PKGCONFIG += sdl

CONFIG += c++11

INCLUDEPATH += glm/

SOURCES += main.cpp \
    tile.cpp \
    l_element.cpp \
    rng_utility.cpp \
    l_system.cpp \
    road_network.cpp

HEADERS += \
    SDLauxiliary.h \
    tile.h \
    l_element.h \
    rng_utility.h \
    l_system.h \
    road_network.h

