# The name of your app.
# NOTICE: name defined in TARGET has a corresponding QML filename.
#         If name defined in TARGET is changed, following needs to be
#         done to match new name:
#         - corresponding QML filename must be changed
#         - desktop icon filename must be changed
#         - desktop filename must be changed
#         - icon definition filename in desktop file must be changed
TARGET = harbour-silicanote

QT += quick qml core sql

QML_IMPORT_PATH += src

CONFIG += sailfishapp

SOURCES += src/Silicanote.cpp \
    src/servercommunicator.cpp \
    src/databasemanager.cpp \
    src/note.cpp \
    src/notelist.cpp \
    src/notemodel.cpp

OTHER_FILES += qml/Silicanote.qml \
    qml/cover/CoverPage.qml \
    rpm/Silicanote.spec \
    qml/pages/storage.js \
    qml/pages/NotePage.qml \
    qml/pages/MainPage.qml \
    rpm/harbour-silicanote.yaml \
    harbour-silicanote.desktop

HEADERS += \
    src/servercommunicator.h \
    src/databasemanager.h \
    src/note.h \
    src/notelist.h \
    src/notemodel.h

