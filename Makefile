TARGET=simMips

INCDIR=include
SRCDIR=src

CFLAGS=-I$(INCDIR) -Wall -Wextra -Wstrict-prototypes -Wshadow -g -ansi -pedantic -O2
LDFLAGS=

SRC=$(wildcard $(SRCDIR)/*.c)
OBJ=$(SRC:.c=.o)

all: sim

sim: $(OBJ)
	gcc $^ $(CFLAGS) $(LDFLAGS) -o $(TARGET)

%.o:%.c
	gcc -c $(CFLAGS) $< -o $(basename $<).o

clean:
	rm $(SRCDIR)/*.o