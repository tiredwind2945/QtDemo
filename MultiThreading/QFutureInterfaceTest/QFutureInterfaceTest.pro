QT              += core gui widgets
QMAKE_CXXFLAGS	+= -Wno-unused-parameter -Wno-unused-variable -Wno-unused-function
TARGET      	=  QFutureInterfaceTest
TEMPLATE    	=  app
UI_DIR      	+= .build
RCC_DIR     	+= .build
MOC_DIR     	+= .build
OBJECTS_DIR 	+= .build
DEFINES 		+= QT_DEPRECATED_WARNINGS

SOURCES += \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    mainwindow.h

FORMS += \
    mainwindow.ui
