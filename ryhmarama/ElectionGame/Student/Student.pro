include( ../common.pri )

QT       += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ElectionGame
TEMPLATE = app

SOURCES +=\
    ../Course/controlexception.cpp \
    ../Course/councilor.cpp \
    ../Course/deck.cpp \
    ../Course/formatexception.cpp \
    ../Course/game.cpp \
    ../Course/gameexception.cpp \
    ../Course/influence.cpp \
    ../Course/ioexception.cpp \
    ../Course/keyexception.cpp \
    ../Course/location.cpp \
    ../Course/manualcontrol.cpp \
    ../Course/player.cpp \
    ../Course/random.cpp \
    ../Course/rangeexception.cpp \
    ../Course/runner.cpp \
    ../Course/settingsreader.cpp \
    ../Course/stateexception.cpp \
    ../Course/withdrawaction.cpp \
    main.cpp \
    agent.cpp \
    mainwindow.cpp \
    actionhandler.cpp

HEADERS  += \
    agent.h \
    mainwindow.h \
    actionhandler.h \
    locationdata.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

INCLUDEPATH += $$PWD/../Course
DEPENDPATH += $$PWD/../Course

CONFIG(release, debug|release) {
    DESTDIR = release
}
CONFIG(debug, debug|release) {
    DESTDIR = debug
}

LIBS += -L$$OUT_PWD/../Course/
LIBS += -L$$OUT_PWD/../Course/$${DESTDIR}/ -lCourse

win32 {
    copyfiles.commands += @echo NOW COPYING ADDITIONAL FILE(S) &
    copyfiles.commands += @call xcopy ..\\..\\$$TARGET\\Assets Assets /i /s /e /y
}
unix {
    copyfiles.commands += @echo \"NOW COPYING ADDITIONAL FILE(S)\" &&
    copyfiles.commands += cp -r ../../$$TARGET/Assets $$DESTDIR
}

QMAKE_EXTRA_TARGETS += copyfiles
POST_TARGETDEPS += copyfiles

FORMS += \
    mainwindow.ui

RESOURCES += \
    resources.qrc
