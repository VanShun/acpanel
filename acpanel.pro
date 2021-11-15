QT       += core gui

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
    aircondctrl.cpp \
    delaytimermanager.cpp \
    homebtns_panel.cpp \
    main.cpp \
    acpanel.cpp \
    modebtns_panel.cpp \
    offbtn_panel.cpp \
    qssmanager.cpp \
    temparc.cpp \
    timedelay.cpp \
    winddirbtns_panel.cpp \
    windspeedbtns_panel.cpp

HEADERS += \
    acpanel.h \
    aircondctrl.h \
    delaytimermanager.h \
    globalsetting.h \
    homebtns_panel.h \
    modebtns_panel.h \
    offbtn_panel.h \
    qssmanager.h \
    temparc.h \
    timedelay.h \
    winddirbtns_panel.h \
    windspeedbtns_panel.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

SUBDIRS += \
    acpanel3.pro

RESOURCES += \
    resources.qrc

DISTFILES += \
    acpanel.pro.user \
    acpanel3.pro.user \
    global.qss \
    m_label_WindDir_Auto.qss \
    m_label_WindDir_LeftRight.qss \
    m_label_WindDir_UpDown.qss \
    m_label_delaytimer_off.qss \
    m_label_delaytimer_on.qss \
    m_label_mode_Automode.qss \
    m_label_mode_Blow.qss \
    m_label_mode_Cold.qss \
    m_label_mode_Dehumid.qss \
    m_label_mode_Heat.qss \
    m_label_windspeed_Auto.qss \
    m_label_windspeed_Gear1.qss \
    m_label_windspeed_Gear2.qss \
    m_label_windspeed_Gear3.qss \
    m_pBtn_Poweroff.qss \
    m_pBtn_Poweron.qss \
    m_pBtn_WindDir_Auto.qss \
    m_pBtn_WindDir_LeftRight.qss \
    m_pBtn_WindDir_UpDown.qss \
    m_pBtn_Windspeed_Auto.qss \
    m_pBtn_Windspeed_Gear1.qss \
    m_pBtn_Windspeed_Gear2.qss \
    m_pBtn_Windspeed_Gear3.qss \
    m_pBtn_Workmode_Automode.qss \
    m_pBtn_Workmode_Blow.qss \
    m_pBtn_Workmode_Cold.qss \
    m_pBtn_Workmode_Dehumid.qss \
    m_pBtn_Workmode_Heat.qss \
    m_pBtn_delayset_timeroff.qss \
    m_pBtn_delayset_timeron.qss
