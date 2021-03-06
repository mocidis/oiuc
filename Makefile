.PHONY:build clean test clean-test

PROTOCOLS_DIR:=../protocols

CPP_SRC:= ./src/ctocpp.cpp \
          ./src/main.cpp \
          ./src/pstn.cpp \
		  ./src/radio.cpp \
		  ./src/backend.cpp \
		  ./src/oiuc.cpp \
		  ./src/oiuc_manager.cpp \
		  ./src/ptt.cpp \
		  ./src/radio_manager.cpp \
		  ./src/log.cpp \
		  ./src/oiuc-config.cpp

GEN_SRC:= gen/arbiter-client.c \
		  gen/arbiter-server.c \
		  gen/oiu-client.c \
		  gen/oiu-server.c

CORE_SRC:= ../concurrent_queue/src/queue.c \
           ../ics/src/ics-command.c \
           ../ics/src/ics.c \
           ../ics/src/ics-event.c \
           ../object-pool/src/object-pool.c \
		   ../common/src/ansi-utils.c

include custom.mk

MY_CFLAGS+=-g $(shell pkg-config --cflags libpjproject json-c) -I$(PROTOCOLS_DIR)/include
MY_LIBS:=-g $(shell pkg-config --libs libpjproject json-c)

APP:=app.app

USERVER_DIR:=../userver
PROTOCOLS_DIR:=../protocols

all: gen-a gen-o build

gen-a: $(PROTOCOLS_DIR)/$(A_PROTOCOL)
	mkdir -p gen
	awk -f $(USERVER_DIR)/gen-tools/gen.awk $(PROTOCOLS_DIR)/arbiter_proto.u
	echo > gen-a

gen-o: $(PROTOCOLS_DIR)/$(O_PROTOCOL)
	mkdir -p gen
	awk -f $(USERVER_DIR)/gen-tools/gen.awk $(PROTOCOLS_DIR)/oiu_proto.u
	echo > gen-o
oiuc.pro:
	echo "## Project file gen by Make" > oiuc.pro
	echo "TEMPLATE = app" >> oiuc.pro
	echo "TARGET = $(APP)" >> oiuc.pro
	echo "OBJECTS_DIR = temp" >> oiuc.pro
	echo "MOC_DIR = temp" >> oiuc.pro
	echo "" >> oiuc.pro
	echo "DEPENDPATH += . \\" >> oiuc.pro
	echo "              include \\" >> oiuc.pro
	echo "              src \\" >> oiuc.pro
	echo "              gen \\" >> oiuc.pro
	echo "              ../concurrent_queue/include \\" >> oiuc.pro
	echo "              ../concurrent_queue/src \\" >> oiuc.pro
	echo "              ../concurrent_queue/test \\" >> oiuc.pro
	echo "              ../ics/include \\" >> oiuc.pro
	echo "              ../ics/src \\" >> oiuc.pro
	echo "              ../ics/test \\" >> oiuc.pro
	echo "              ../object-pool/include \\" >> oiuc.pro
	echo "              ../object-pool/src \\" >> oiuc.pro
	echo "              ../common/include \\" >> oiuc.pro
	echo "              ../common/src" >> oiuc.pro
	echo "" >> oiuc.pro
	echo "INCLUDEPATH += . \\" >> oiuc.pro
	echo "               include \\" >> oiuc.pro
	echo "               gen \\" >> oiuc.pro
	echo "               ../ics/include \\" >> oiuc.pro
	echo "               ../concurrent_queue/include \\" >> oiuc.pro
	echo "               ../object-pool/include \\" >> oiuc.pro
	echo "               ../common/include" >> oiuc.pro
	echo "" >> oiuc.pro
	echo "QT += declarative sql" >> oiuc.pro
	echo "QMAKE_CFLAGS += $(MY_CFLAGS)" >> oiuc.pro
	echo "QMAKE_CXXFLAGS += $(MY_CFLAGS)" >> oiuc.pro
	echo "QMAKE_LIBS += $(MY_LIBS)" >> oiuc.pro
	echo "" >> oiuc.pro
	echo "HEADERS += $(subst /src/,/include/,$(CPP_SRC:.cpp=.h)) $(GEN_SRC:.c=.h) $(subst /src/,/include/,$(CORE_SRC:.c=.h))" >> oiuc.pro
	echo "" >> oiuc.pro
	echo "SOURCES += $(CPP_SRC) $(GEN_SRC) $(CORE_SRC)" >> oiuc.pro

Makefile.qt.mk: oiuc.pro
	qmake -makefile $(QMAKE_OPT) $< -o $@

build: Makefile.qt.mk
	make -f Makefile.qt.mk 

clean:
	make clean -f Makefile.qt.mk
	rm -fr temp oiuc.pro Makefile.qt.mk gen $(APP) gen-a gen-o /tmp/oiuc.log

test:
	make -f Makefile.quy

clean-test:
	make -f Makefile.quy clean
