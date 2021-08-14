QT       += core gui
QT       += network
QT       += xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    chatbox.cpp \
    clientmanager.cpp \
    dialog.cpp \
    login.cpp \
    main.cpp
    #test.cpp

HEADERS += \
    chatbox.h \
    clientmanager.h \
    dialog.h \
    login.h
    #test.h

FORMS += \
    chatbox.ui \
    dialog.ui \
    login.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES +=

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../../../usr/local/lib/release/ -lqxmpp
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../../../usr/local/lib/debug/ -lqxmpp
else:unix: LIBS += -L$$PWD/../../../../../usr/local/lib/ -lqxmpp

INCLUDEPATH += $$PWD/../../../../../usr/local/include/qxmpp/
DEPENDPATH += $$PWD/../../../../../usr/local/include/qxmpp/
