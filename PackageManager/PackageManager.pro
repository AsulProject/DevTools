QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    PackageManager.cpp \

HEADERS += \
    PackageManager.h \


INCLUDEPATH += $$PWD/include
INCLUDEPATH += $$PWD/src

HEADERS += $$files($$PWD/include/stdafx/*.h,true)

HEADERS += $$files($$PWD/include/asulException/*.h,true)

HEADERS += $$files($$PWD/include/asulSignal/*.h,true)
SOURCES += $$files($$PWD/src/asulSignal/*.cpp,true)

HEADERS += $$files($$PWD/include/asulSignalManager/*.h,true)
SOURCES += $$files($$PWD/src/asulSignalManager/*.cpp,true)

HEADERS += $$files($$PWD/include/asulSubscription/*.h,true)
SOURCES += $$files($$PWD/src/asulSubscription/*.cpp,true)

HEADERS += $$files($$PWD/include/asulPackage/*.h,true)
SOURCES += $$files($$PWD/src/asulPackage/*.cpp,true)

HEADERS += $$files($$PWD/include/asulPackageManager/*.h,true)
SOURCES += $$files($$PWD/src/asulPackageManager/*.cpp,true)

HEADERS += $$files($$PWD/include/asulVirtualFilesystem/*.h,true)
SOURCES += $$files($$PWD/src/asulVirtualFilesystem/*.cpp,true)

HEADERS += $$files($$PWD/include/QStringModifier/*.h,true)
SOURCES += $$files($$PWD/src/QStringModifier/*.cpp,true)



FORMS += \
    PackageManager.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
