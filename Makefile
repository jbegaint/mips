TARGET=simMips

INCDIR=include
SRCDIR=src

CFLAGS=-I$(INCDIR) -Wall -Wextra -Wshadow -g -ansi -pedantic -O2
LDFLAGS=-lreadline -lcurses

SRC=$(wildcard $(SRCDIR)/*.c)
OBJ=$(SRC:.c=.o)
BUILDDIR=bin


SOURCES := $(shell find $(SRCDIR) -name '*.c')

# list of object files, with paths
OBJECTS := $(addprefix $(BUILDDIR)/, $(SOURCES:%.c=%.o))

sim: $(OBJECTS)
	gcc $^ $(CFLAGS) $(LDFLAGS) -o $(TARGET)

$(BUILDDIR)/%.o: %.c
	gcc $(CFLAGS) $(LDFLAGS) -I$(HEADERDIR) -I$(dir $<) -c $< -o $@

# all: sim

# sim: $(OBJ)
# 	gcc $^ $(CFLAGS) $(LDFLAGS) -o $(TARGET)

# %.o: %.c
# 	gcc -c $(CFLAGS) $< -o $(basename $<).o

# clean:
	# rm $(SRCDIR)/*.o

check:
	./simpleUnitTest.sh -e simMips -b tests/*.simcmd

