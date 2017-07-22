# Compiler for the default rule to use.
CC = gcc

# extra options we want the default compile rule to use.
CFLAGS = -Wall  -std=c99
all: encrypt decrypt

# Main depends on main.o (implicit) and function.o
encrypt: code.o bits.o
decrypt: code.o bits.o

# Our objects depend on their own source files (implicit),
# and this one header.
# BTW, there are tools that will auto-generate these dependencies
# for you, by looking at your source code.

code.o: code.h
bits.o: bits.h

clean:
	rm -f encrypt decrypt
	rm -f code.o bits.o
	rm output.txt
	rm stdout.txt
	rm stderr.txt
