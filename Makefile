TARGET=simMips

INC_DIR=include
SRC_DIR=src

CFLAGS=-I$(INC_DIR) -Wall -Wextra -Wshadow -g -std=c99 -pedantic -O2 -DDEBUG
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