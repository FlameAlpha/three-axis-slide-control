QT += widgets serialport
QT += 3dextras
RC_FILE += myico.rc

TARGET = X_Y_Z_Drawer
TEMPLATE = app
QT+= core gui
QT += datavisualization

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    settingsdialog.cpp \
    console.cpp \
    motorcontrol.cpp

HEADERS += \
    mainwindow.h \
    settingsdialog.h \
    console.h \
    motorcontrol.h

FORMS += \
    mainwindow.ui \
    settingsdialog.ui \
    motorcontrol.ui

RESOURCES += \
    X_Y_Z_Drawer.qrc

target.path = $$[QT_INSTALL_EXAMPLES]/serialport/terminal
INSTALLS += target

DISTFILES +=
