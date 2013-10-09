TARGET=simMips

INCDIR=include
SRCDIR=src

CFLAGS=-I$(INCDIR) -Wall -Wextra -Wshadow -g -ansi -pedantic -O2
LDFLAGS=-lreadline -lcurses

SRC=$(wildcard $(SRCDIR)/*.c)
OBJ=$(SRC:.c=.o)
BUILDDIR=bin

SOURCES := $(shell find $(SRCDIR) -name '*.c')
OBJS := $(shell find $(BUILDDIR) -name '*.o')

# list of object files, with paths
OBJECTS := $(addprefix $(BUILDDIR)/, $(SOURCES:%.c=%.o))

all: sim

sim: $(OBJECTS)
	@gcc $^ $(CFLAGS) $(LDFLAGS) -o $(TARGET)

$(BUILDDIR)/%.o: %.c
	@gcc $(CFLAGS) $(LDFLAGS) -I$(HEADERDIR) -I$(dir $<) -c $< -o $@

clean:
	@rm $(OBJS)

check:
	./simpleUnitTest.sh -e simMips -b tests/*.simcmd

