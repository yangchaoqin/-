######################################################################
# Automatically generated by qmake (2.01a) ?? ?? 23 19:27:34 2014
######################################################################

TEMPLATE = lib
TARGET = SIpcObject
CONFIG(x64){
TARGET = $$TARGET"64"
}
!LIB_ALL:!COM_LIB{
	RC_FILE += SIpcObject.rc
	CONFIG += dll
	DEFINES += BUILD_SIPC
}
else{
	DEFINES += _LIB
	CONFIG += staticlib
}


DEPENDPATH += .
INCLUDEPATH += . \
			   ../../utilities/include \
			   ../../soui/include \

dir = ../..
include($$dir/common.pri)

PRECOMPILED_HEADER = stdafx.h

# Input
HEADERS += SIpcObject.h ShareMemBuffer.h
SOURCES += SIpcObject.cpp ShareMemBuffer.cpp
