#-------------------------------------------------
#
# Project created by QtCreator 2014-03-29T10:07:06
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TextDump
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
        single_message_box.cpp \
        multi_message_box.cpp \
        manager.cpp \
		gui.cpp \
		hot_key_listener.cpp

HEADERS  += mainwindow.h \
            single_message_box.h \
            multi_message_box.h \
            manager.h \
			gui.h \
			message.h \
			hot_key_listener.h

FORMS    += mainwindow.ui \
            single_message_box.ui \
			multi_message_box.ui \
    userinfoform.ui

RESOURCES += textdumpicons.qrc
