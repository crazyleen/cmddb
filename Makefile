

CC ?= gcc

ifdef WITHOUT_READLINE
	READLINE_CFLAGS =
	READLINE_LIBS =
else
	READLINE_CFLAGS = -DUSE_READLINE
	READLINE_LIBS = -lreadline
endif

CFLAGS = -O2 -Wall -Wno-char-subscripts $(READLINE_CFLAGS) 
LDFLAGS = -s

INCLUDES = -I. -Iui -Iutil
LIBS = $(READLINE_LIBS) $(OS_LIBS)

BINARY = cmddb
all: $(BINARY)

.SUFFIXES: .c .o

OBJ=\
	util/util.o \
    ui/reader.o \
    ui/input.o \
    ui/input_console.o \
    ui/command.o \
    ui/cmddb.o \
    ui/main.o
    

$(BINARY): $(OBJ)
	$(CC) $(LDFLAGS) -o $@ $^ $(LIBS)

.c.o:
	$(CC) $(INCLUDES) $(CFLAGS) -o $@ -c $*.c


clean:
	@rm -f $(OBJ)
	@rm -f $(BINARY)
