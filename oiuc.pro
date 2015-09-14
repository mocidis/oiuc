######################################################################
# Automatically generated by qmake (2.01a) Mon Sep 7 20:31:29 2015
######################################################################

TEMPLATE = app
TARGET = app.app
OBJECTS_DIR = temp
MOC_DIR = temp

DEPENDPATH += . \
              include \
              src \
              ../concurrent_queue/include \
              ../concurrent_queue/src \
              ../concurrent_queue/test \
              ../ics/include \
              ../ics/src \
              ../ics/test \
              ../object-pool/include \
              ../object-pool/src \
              ../common/include \
              ../common/src
INCLUDEPATH += . \
               include \
               ../ics/include \
               ../concurrent_queue/include \
               ../object-pool/include \
               ../common/include

# Input
QT += declarative sql
QMAKE_CFLAGS += $(shell pkg-config --cflags /usr/local/lib/pkgconfig/libpjproject.pc)
QMAKE_LIBS += $(shell pkg-config --libs /usr/local/lib/pkgconfig/libpjproject.pc)

HEADERS += include/ctocpp.h \
           include/pstn.h \
		   include/radio.h \
		   include/group.h \
		   include/backend.h \
		   include/group_manager.h \
           ../concurrent_queue/include/queue.h \
           ../ics/include/db-utils.h \
           ../ics/include/ics-command.h \
           ../ics/include/ics-common.h \
           ../ics/include/ics.h \
           ../ics/include/ics-event.h \
           ../object-pool/include/object-pool.h \
		   ../common/include/ansi-utils.h
SOURCES += src/ctocpp.cpp \
           src/main.cpp \
           src/pstn.cpp \
		   src/radio.cpp \
		   src/group.cpp \
		   src/backend.cpp \
		   src/group_manager.cpp \
           ../concurrent_queue/src/queue.c \
           ../ics/src/ics-command.c \
           ../ics/src/ics.c \
           ../ics/src/ics-event.c \
           ../object-pool/src/object-pool.c \
		   ../common/src/ansi-utils.c