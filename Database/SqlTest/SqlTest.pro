QT       		+= core gui sql widgets
QMAKE_CXXFLAGS	+= -Wno-unused-parameter -Wno-unused-variable -Wno-unused-function
TARGET      	=  SqlTest
TEMPLATE    	=  app
UI_DIR      	+= .build
RCC_DIR     	+= .build
MOC_DIR     	+= .build
OBJECTS_DIR 	+= .build
CONFIG += c++17

SOURCES += \
    main.cpp \
    widget.cpp

HEADERS += \
    connection.h \
    widget.h

FORMS += \
    widget.ui