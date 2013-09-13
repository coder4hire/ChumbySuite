#-------------------------------------------------
#
# Project created by QtCreator 2011-05-14T23:06:33
#
#-------------------------------------------------

QT       += core gui webkit

TARGET = ChumbySuite
TEMPLATE = app


SOURCES += main.cpp\
    cwidgetbase.cpp \
    CMainWindowWidget.cpp \
    CMP3Widget.cpp \
    WidgetSelector.cpp \
    Fader.cpp \
    Settings.cpp \
    ConfigDlg.cpp \
    ConfigWidgetBase.cpp \
    ConfigMainWindow.cpp \
    WebBrowserWidget.cpp \
    NetworkTools.cpp \
    NumericKbd.cpp \
    KbdEditBox.cpp \
    EnglishKbd.cpp \
    KbdBase.cpp \
    MP3PlayerCore.cpp \
    FolderDialog.cpp \
    ClockWidget.cpp \
    AlarmClockWidget.cpp \
    ScheduleListDelegate.cpp \
    ScheduleView.cpp \
    ScheduleViewAddEditDlg.cpp \
    HardwareLayer.cpp \
    Log.cpp \
    MP3ListModel.cpp \
    BTPlayDrv.cpp \
    VolumeControlDlg.cpp \
    AlarmMessageDlg.cpp \
    RadioWidget.cpp \
    NightWidget.cpp

HEADERS  += \
    cwidgetbase.h \
    CMainWindowWidget.h \
    CMP3Widget.h \
    WidgetSelector.h \
    Fader.h \
    Settings.h \
    ConfigDlg.h \
    ConfigWidgetBase.h \
    ConfigMainWindow.h \
    WebBrowserWidget.h \
    NetworkTools.h \
    NumericKbd.h \
    KbdEditBox.h \
    EnglishKbd.h \
    KbdBase.h \
    MP3PlayerCore.h \
    FolderDialog.h \
    ClockWidget.h \
    AlarmClockWidget.h \
    ScheduleListDelegate.h \
    ScheduleView.h \
    ScheduleViewAddEditDlg.h \
    HardwareLayer.h \
    Log.h \
    MP3ListModel.h \
    BTPlayDrv.h \
    VolumeControlDlg.h \
    AlarmMessageDlg.h \
    RadioWidget.h \
    NightWidget.h

FORMS    += \
    CMainWindowWidget.ui \
    CMP3Widget.ui \
    WidgetSelector.ui \
    ConfigDlg.ui \
    ConfigMainWindow.ui \
    WebBrowserWidget.ui \
    NumericKbd.ui \
    EnglishKbd.ui \
    CFolderDialog.ui \
    AlarmClockWidget.ui \
    ScheduleViewAddEditDlg.ui \
    VolumeControlDlg.ui \
    AlarmMessageDlg.ui \
    RadioWidget.ui \
    NightWidget.ui

CONFIG += console

RESOURCES += \
    Resources.qrc

OTHER_FILES += \
    Resources/default.css
