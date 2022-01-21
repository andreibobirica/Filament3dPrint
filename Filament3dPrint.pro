#-------------------------------------------------
#
# Project created by QtCreator 2022-01-10T21:22:43
#
#-------------------------------------------------

QT += core charts

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Filament3dPrint
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
    main.cpp \
    view/homeview.cpp \
    view/adminview.cpp \
    ctrl/homectrl.cpp \
    view/view.cpp \
    ctrl/ctrl.cpp \
    ctrl/adminctrl.cpp \
    model/model.cpp \
    ctrl/jsonfilepicker.cpp \
    model/adminmodel.cpp \
    model/record.cpp \
    view/piechartview.cpp \
    model/piechartmodel.cpp \
    ctrl/piechartctrl.cpp \
    view/piechartdetailview.cpp \
    view/linechartview.cpp \
    ctrl/linechartctrl.cpp

HEADERS += \
    view/homeview.h \
    view/adminview.h \
    ctrl/homectrl.h \
    view/view.h \
    ctrl/ctrl.h \
    ctrl/adminctrl.h \
    model/model.h \
    ctrl/jsonfilepicker.h \
    model/adminmodel.h \
    model/record.h \
    view/piechartview.h \
    model/piechartmodel.h \
    ctrl/piechartctrl.h \
    view/piechartdetailview.h \
    view/linechartview.h \
    ctrl/linechartctrl.h


DISTFILES += \
    3d.jpg \
    myicon.ico

STATECHARTS +=
