.PHONY: all clean test doc

APP:=oiuc
TESTS:=oiuc.c

DIR:=.
PROTOCOLS_DIR:=../protocols

ICS_DIR:=../ics
ICS_SRCS:=ics.c ics-event.c ics-command.c

C_DIR:=../common
C_SRCS:=ansi-utils.c

GEN_DIR:=./gen
GEN_C_SRCS:=arbiter-client.c
GEN_S_SRCS:=oiu-server.c

Q_DIR:=../concurrent_queue
Q_SRCS:=queue.c

O_DIR:=../object-pool
O_SRCS:=object-pool.c

USERVER_DIR:=../userver
ARBITER_DIR:=../arbiter

CFLAGS:=-std=c99 $(shell pkg-config --cflags libpjproject) -Werror
CFLAGS+=-I$(ICS_DIR)/include -I$(Q_DIR)/include -I$(O_DIR)/include
CFLAGS+=-I$(C_DIR)/include -I$(USERVER_DIR)/include
CFLAGS+= -I../json-c/output/include/json-c
CFLAGS+= -I../arbiter/include
CFLAGS+= -D_GNU_SOURCE
CFLAGS += -I$(GEN_DIR)

LIBS:=$(shell pkg-config --libs libpjproject) ../json-c/output/lib/libjson-c.a -lpthread

A_PROTOCOL:=arbiter_proto.u
O_PROTOCOL:=oiu_proto.u

all: gen-a gen-o $(APP)

gen-a: $(PROTOCOLS_DIR)/$(A_PROTOCOL)
	mkdir -p gen
	awk -f $(USERVER_DIR)/gen-tools/gen.awk $(PROTOCOLS_DIR)/arbiter_proto.u

gen-o: $(PROTOCOLS_DIR)/$(O_PROTOCOL)
	mkdir -p gen
	awk -f $(USERVER_DIR)/gen-tools/gen.awk $(PROTOCOLS_DIR)/oiu_proto.u

doc: html latex
	doxygen
html:
	mkdir -p $@
latex:
	mkdir -p $@

$(APP): $(SRCS:.c=.o) $(TESTS:.c=.o) $(Q_SRCS:.c=.o) $(O_SRCS:.c=.o) $(C_SRCS:.c=.o) $(USERVER_C_SRCS:.c=.o) $(GEN_S_SRCS:.c=.o) $(GEN_C_SRCS:.c=.o) $(ICS_SRCS:.c=.o)
	gcc -o $@ $^ $(LIBS)

$(GEN_C_SRCS:.c=.o): %.o: $(GEN_DIR)/%.c
	gcc -o $@ -c $< $(CFLAGS)

$(GEN_S_SRCS:.c=.o): %.o: $(GEN_DIR)/%.c
	gcc -o $@ -c $< $(CFLAGS)

$(TESTS:.c=.o): %.o: $(DIR)/src/%.c
	gcc -c -o $@ $< $(CFLAGS)

$(ICS_SRCS:.c=.o): %.o: $(ICS_DIR)/src/%.c
	gcc -c -o $@ $< $(CFLAGS)
$(O_SRCS:.c=.o): %.o: $(O_DIR)/src/%.c
	gcc -c -o $@ $< $(CFLAGS)

$(Q_SRCS:.c=.o): %.o: $(Q_DIR)/src/%.c
	gcc -c -o $@ $< $(CFLAGS)
$(C_SRCS:.c=.o): %.o: $(C_DIR)/src/%.c
	gcc -c -o $@ $< $(CFLAGS)
$(USERVER_C_SRCS:.c=.o): %.o: $(USERVER_DIR)/src/%.c
	gcc -o $@ -c $< $(CFLAGS)

clean:
	rm -fr *.o $(APP) $(LOG) html latex gen