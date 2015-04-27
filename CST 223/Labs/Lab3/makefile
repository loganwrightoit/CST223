# Simple Makefile for compiling a single file program
#
#Makefile variable definitions
CC = /usr/bin/gcc
LD = /usr/bin/gcc
CFLAGS = -g -Wall -O3
LDFLAGS =
RM = /bin/rm -f
#
#Variables for the file being compiled
###########################
NAME = sort
###########################
#
OBJS = $(NAME).o
PROG = $(NAME)
SRC = $(NAME).c

all: $(PROG)

$(PROG): $(OBJS)
	$(LD) $(LDFLAGS) $(OBJS) -o $(PROG)

$(OBJS):  $(SRC)
	$(CC) $(CFLAGS) -c $(SRC)

clean:
	$(RM) $(PROG) $(OBJS)
