#!smake
PROGRAM=tcpecho
CC=cc
CFLAGS=
LDFLAGS=

RM=rm
RMFLAGS=-f

SRCS=echo.c
OBJS=${SRCS:S/.c/.o/g}

all: $(PROGRAM)

$(PROGRAM): $(OBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $(PROGRAM) $(OBJS)

clean:
	$(RM) $(RMFLAGS) $(PROGRAM)
	$(RM) $(RMFLAGS) $(OBJS)
