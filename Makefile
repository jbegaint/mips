TARGET=simMips

INC_DIR=include
SRC_DIR=src
BUILD_DIR=bin

CFLAGS=-I$(INC_DIR) -Wall -Wextra -Wshadow -g -ansi -pedantic -O2
LDFLAGS=-lreadline -lcurses


SOURCES := $(shell find $(SRC_DIR) -name '*.c')

# list of object files, with paths
OBJECTS := $(SOURCES:%.c=%.o)

all: simMips 

simMips: $(OBJECTS)
	@gcc $^ $(CFLAGS) $(LDFLAGS) -o $(TARGET)

%.o: %.c
	@gcc $< $(CFLAGS) $(LDFLAGS) -I$(dir $<) -c -o $@

clean:
	rm -f $(OBJECTS)

check:
	./simpleUnitTest.sh -e simMips -b tests/*.simcmd