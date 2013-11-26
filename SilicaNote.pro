# The name of your app.
# NOTICE: name defined in TARGET has a corresponding QML filename.
#         If name defined in TARGET is changed, following needs to be
#         done to match new name:
#         - corresponding QML filename must be changed
#         - desktop icon filename must be changed
#         - desktop filename must be changed
#         - icon definition filename in desktop file must be changed
TARGET = Silicanote

CONFIG += sailfishapp

SOURCES += src/Silicanote.cpp \
    src/servercommunicator.cpp

OTHER_FILES += qml/Silicanote.qml \
    qml/cover/CoverPage.qml \
    rpm/Silicanote.spec \
    rpm/Silicanote.yaml \
    Silicanote.desktop \
    qml/pages/storage.js \
    qml/pages/NotePage.qml \
    qml/pages/MainPage.qml

HEADERS += \
    src/servercommunicator.h

