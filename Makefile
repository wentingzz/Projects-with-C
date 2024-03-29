# Compiler for the default rule to use.
CC = gcc

# extra options we want the default compile rule to use.
CFLAGS = -Wall -std=c99 -g

# Main
drawing: model.o scene.o

model: model.h
	gcc -Wall -std=c99 -c model.c -lm
scene.o: scene.h
	gcc -Wall -std=c99 -c scene.c -lm

clean:
	rm -f drawing
	rm -f drawing.o model.o scene.o
	rm output.txt
	rm stdout.txt
	rm stderr.txt
