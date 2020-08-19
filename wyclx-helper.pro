QT       += core gui axcontainer

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
    dm.cpp \
    game-interface/featurepoint.cpp \
    game-interface/gameinterface.cpp \
    game-interface/rewordinstance.cpp \
    game-interface/rewordinterface.cpp \
    instance.cpp \
    main.cpp \
    mainwindow.cpp \
    script/abstractscript.cpp \
    script/dailytaskscript.cpp \
    script/rewordscript.cpp \
    window-controller/bitmap.cpp \
    window-controller/color.cpp \
    window-controller/point.cpp \
    window-controller/size.cpp \
    window-controller/windowcontrol.cpp

HEADERS += \
    dm.h \
    game-interface/featurepoint.h \
    game-interface/gameinterface.h \
    game-interface/rewordinstance.h \
    game-interface/rewordinterface.h \
    instance.h \
    mainwindow.h \
    script/abstractscript.h \
    script/dailytaskscript.h \
    script/rewordscript.h \
    window-controller/bitmap.h \
    window-controller/color.h \
    window-controller/point.h \
    window-controller/size.h \
    window-controller/windowcontrol.h

FORMS += \
    mainwindow.ui

RC_FILE = resource.rc
RC_ICONS= resource/images/qc.ico

DISTFILES += \
    resource.rc \
    resource/images/down.png \
    resource/images/icon.jpg \
    resource/images/qc.ico \
    resource/images/qc.jpg \
    resource/images/up.png \
    resource/settings.ini \
    uac.manifest \
    lib/RegDll.dll \
    lib/dm.dll \
    resource/reword_number.txt

win32: LIBS += -lGdi32

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

