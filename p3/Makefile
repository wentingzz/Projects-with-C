# Compiler for the default rule to use.
CC = gcc

# extra options we want the default compile rule to use.
CFLAGS = -Wall -std=c99

all: jumble puzzle puzzle.o grid.o
# Main depends on main.o (implicit) and function.o
jumble: jumble.o
puzzle: grid.o

# Our objects depend on their own source files (implicit),
# and this one header.
# BTW, there are tools that will auto-generate these dependencies
# for you, by looking at your source code.

puzzle.o: grid.h
grid.o: grid.h

#clean:
#	rm -rf *o puzzle
