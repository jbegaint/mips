TARGET=simMips

INC_DIR=include
SRC_DIR=src
PLUGINS_DIR=descs

CFLAGS=-I$(INC_DIR) -Wall -Wextra -Wshadow -std=c99 -pedantic
CFLAGS_RLS=$(CFLAGS) 
CFLAGS_DBG=$(CFLAGS) -g -DDEBUG -DVERBOSE -O0
CFLAGS_DYNAMIC=$(CFLAGS) -shared -fPIC

LDFLAGS=-lreadline -lcurses -lelf -lm -ldl
LDFLAGS_DYNAMIC=$(LDFLAGS) -rdynamic

SOURCES := $(shell find $(SRC_DIR) -name '*.c' ! -name "mipself_test.c")
PLUGINS_SRC := $(shell find $(PLUGINS_DIR) -name '*.c')

OBJECTS := $(SOURCES:%.c=%.o)
OBJECTS_DBG := $(SOURCES:%.c=%.dbg.o)
OBJECTS_SO := $(PLUGINS_SRC:%.c=%.so)

all: simMips plugins

simMips: $(OBJECTS)
	@gcc $^ $(LDFLAGS_DYNAMIC) -o $(TARGET)

simMips-debug: $(OBJECTS_DBG)
	@gcc $^ $(LDFLAGS_DYNAMIC) -o $(TARGET)

plugins: $(OBJECTS_SO)
	
%.o: %.c
	@gcc $< $(CFLAGS_RLS) -I$(dir $<) -c -o $@

%.dbg.o : %.c
	@gcc $< $(CFLAGS_DBG) -I$(dir $<) -c -o $@

%.so : %.c
	@gcc $< $(CFLAGS_DYNAMIC) -I$(dir $<)  -o $@

.PHONY: clean doc check

clean:
	@rm -f $(OBJECTS) $(OBJECTS_DBG)
	@rm -f descs/*.so

doc:
	@doxygen

check:
	./simpleUnitTest.sh -e simMips -b tests/{*.simcmd,*/*.simcmd}
	# ./simpleUnitTest.sh -e simMips -b tests/*.simcmd
	
# for testing purpose 
mipself_test: src/elf/mipself_test.o src/elf/mipself.o
	gcc $^ $(CFLAGS) $(LDFLAGS) -o $@
