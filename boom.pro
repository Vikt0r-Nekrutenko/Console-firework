TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        main.c \
        particle.c \
        renderer.c \
        vector2d.c \
        window.c

HEADERS += \
    boom_type.h \
    particle.h \
    renderer.h \
    vector2d.h \
    window.h
