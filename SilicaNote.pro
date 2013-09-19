# The name of your app
TARGET = SilicaNote

# C++ sources
SOURCES += main.cpp

# C++ headers
HEADERS +=

# QML files and folders
qml.files = *.qml pages cover main.qml

# The .desktop file
desktop.files = SilicaNote.desktop

# Please do not modify the following line.
include(sailfishapplication/sailfishapplication.pri)

OTHER_FILES = rpm/SilicaNote.yaml \
    js/storage.js \
    rpm/SilicaNote.spec

