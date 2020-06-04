TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        main.c \
        renderer.c \
        vector2d.c \
        window.c

HEADERS += \
    renderer.h \
    vector2d.h \
    window.h
