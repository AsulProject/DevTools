QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# LIBS += -lpsapi # Winapi to access to Windows
# RC_FILE += res.rc  # Require UAC for Admin Using Function
# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    QStringModifier.cpp \
    main.cpp \
    jsonparser.cpp

HEADERS += \
    QStringModifier.h \
    jsonparser.h \
    stdafx.h

FORMS += \
    jsonparser.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc
