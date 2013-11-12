TARGET=simMips

INC_DIR=include
SRC_DIR=src

# CFLAGS=-I$(INC_DIR) -Wall -Wextra -Wshadow -std=c99 -pedantic
CFLAGS=-I$(INC_DIR) -Wall -std=c99 -pedantic

CFLAGS_RLS=$(CFLAGS) -O2
CFLAGS_DBG=$(CFLAGS) -g -DDEBUG -DVERBOSE

LDFLAGS=-lreadline -lcurses -lelf -lm

SOURCES := $(shell find $(SRC_DIR) -name '*.c' ! -name "mipself_test.c")

# list of object files, with paths
OBJECTS := $(SOURCES:%.c=%.o)
OBJECTS_DBG := $(SOURCES:%.c=%.dbg.o)

all: simMips-debug

simMips: $(OBJECTS)
	@gcc $^ $(LDFLAGS) -o $(TARGET)

simMips-debug: $(OBJECTS_DBG)
	@gcc $^ $(LDFLAGS) -o $(TARGET)

%.o: %.c
	@gcc $< $(CFLAGS_RLS) -I$(dir $<) -c -o $@

%.dbg.o : %.c
	@gcc $< $(CFLAGS_DBG) -I$(dir $<) -c -o $@

clean:
	@rm -f $(OBJECTS) $(OBJECTS_DBG)

doc:
	@doxygen

check:
	./simpleUnitTest.sh -e simMips -b tests/*.simcmd


# for testing purpose 
mipself_test: src/elf/mipself_test.o src/elf/mipself.o
	gcc $^ $(CFLAGS) $(LDFLAGS) -o $@
