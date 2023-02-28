QT       += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
TARGET = GraphicsTest
TEMPLATE = app
UI_DIR      	+= .build
RCC_DIR     	+= .build
MOC_DIR     	+= .build
OBJECTS_DIR 	+= .build
DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += \
        main.cpp \
        widget.cpp

HEADERS += \
        widget.h

FORMS += \
        widget.ui
