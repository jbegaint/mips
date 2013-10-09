TARGET=simMips

INCDIR=include
SRCDIR=src
BUILDDIR=bin

CFLAGS=-I$(INCDIR) -Wall -Wextra -Wshadow -g -ansi -pedantic -O2
LDFLAGS=-lreadline -lcurses


SOURCES := $(shell find $(SRCDIR) -name '*.c')
OBJS := $(shell find $(BUILDDIR) -name '*.o')

# list of object files, with paths
OBJECTS := $(addprefix $(BUILDDIR)/, $(SOURCES:%.c=%.o))

all: simMips
	
simMips: $(OBJECTS)
	@echo make simMips
	@gcc $^ $(CFLAGS) $(LDFLAGS) -o $(TARGET)

$(BUILDDIR)/%.o: %.c
	@gcc $(CFLAGS) $(LDFLAGS) -I$(HEADERDIR) -I$(dir $<) -c $< -o $@

clean:
	@echo clean *.o
	@rm $(OBJS)

check:
	./simpleUnitTest.sh -e simMips -b tests/*.simcmd