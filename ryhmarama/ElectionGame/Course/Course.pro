include( ../common.pri )

QT       += core

TARGET = Course
CONFIG += staticlib

HEADERS += \
    agentinterface.h \
    cardinterface.h \
    deckinterface.h \
    game.h \
    influence.h \
    location.h \
    player.h \

unix {
    target.path = /usr/lib
    INSTALLS += target
}
