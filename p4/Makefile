# Compiler for the default rule to use.
CC = gcc

# extra options we want the default compile rule to use.
CFLAGS = -Wall -std=c99 -g
LIBS = -lm

# Main depends on main.o (implicit) and function.o
drawing: model.o scene.o

# Our objects depend on their own source files (implicit),
# and this one header.
# BTW, there are tools that will auto-generate these dependencies
# for you, by looking at your source code.

model: model.h
scene.o: scene.h

clean:
	rm -f drawing
	rm -f drawing.o model.o scene.o
	rm output.txt
	rm stdout.txt
	rm stderr.txt
