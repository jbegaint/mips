TARGET=simMips

INC_DIR=include
SRC_DIR=src

CFLAGS=-I$(INC_DIR) -Wall -Wextra -Wshadow -std=c99 -pedantic #-O2

CFLAGS_RLS=$(CFLAGS)
CFLAGS_DBG=$(CFLAGS) -g -DDEBUG -DVERBOSE

LDFLAGS=-lreadline -lcurses -lelf -lm

SOURCES := $(shell find $(SRC_DIR) -name '*.c' ! -name "mipself_test.c")

# list of object files, with paths
OBJECTS := $(SOURCES:%.c=%.o)
OBJECTS_DBG := $(SOURCES:%.c=%.dbg.o)

all: simMips-debug mipself_test

simMips: $(OBJECTS)
	@gcc $^ $(CFLAGS) $(LDFLAGS) -o $(TARGET)

simMips-debug: $(OBJECTS_DBG)
	@gcc $^ $(CFLAGS) $(LDFLAGS) -o $(TARGET)

%.o: %.c
	@gcc $< $(CFLAGS) $(LDFLAGS) -I$(dir $<) -c -o $@

%.dbg.o : %.c
	@gcc $< $(CFLAGS) $(CFLAGS_DBG) -I$(dir $<) -c -o $@

clean:
	@rm -f $(OBJECTS) $(OBJECTS_DBG)

doc:
	@doxygen

check:
	./simpleUnitTest.sh -e simMips -b tests/*.simcmd


# for testing purpose 
mipself_test: src/elf/mipself_test.o src/elf/mipself.o
	@gcc $^ $(CFLAGS) $(LDFLAGS) -o $@
