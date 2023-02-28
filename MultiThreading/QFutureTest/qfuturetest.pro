#---------------------------------------------------------------------------
#
# Author:              wangjun
# E-Mail:              jwang3
# Phone Number:        15256527665
# Creation Time:       2023-02-28
#
# Description: 此Demo展示了QFuture和QFutureWatcher的用法，用异步方式加载并展示多张图片
#
#---------------------------------------------------------------------------

QT          	+= core gui widgets concurrent
QMAKE_CXXFLAGS	+= -Wno-unused-parameter -Wno-unused-variable -Wno-unused-function
TARGET      	=  QFutureTest
TEMPLATE    	=  app
UI_DIR      	+= .build
RCC_DIR     	+= .build
MOC_DIR     	+= .build
OBJECTS_DIR 	+= .build
DEFINES     	+= QT_DEPRECATED_WARNINGS

INCLUDEPATH += \
	./include

SOURCES     += \
	main.cpp \
	mainwindow.cpp

HEADERS     += \
	mainwindow.h \
	include/constexpr_string.h

FORMS       += \
	mainwindow.ui
