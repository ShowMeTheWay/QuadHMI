#-------------------------------------------------
#
# Project created by QtCreator 2019-03-25T14:11:36
#
#-------------------------------------------------

QT       += core gui serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = motorsTestPanel
TEMPLATE = app


SOURCES += main.cpp\
    gd_plot.cpp \
    main_window.cpp \
    gd_chart.cpp \
    chart_settings.cpp \
    scomdialog.cpp \
    serial_connection_status.cpp \
    serial_conn_info.cpp

HEADERS  += \
    gd_plot.h \
    main_window.h \
    gd_chart.h \
    chart_settings.h \
    scomdialog.h \
    serial_connection_status.h \
    serial_conn_info.h

FORMS    += mainwindow.ui
